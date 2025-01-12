#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* See LICENSE file for copyright and license details. */

/* interval between updates (in ms) */
const unsigned int interval = 1000;

/* text to show if no value can be retrieved */
static const char unknown_str[] = "n/a";

/* maximum output string length */
#define MAXLEN 2048

/*
 * function            description                     argument (example)
 *
 * battery_perc        battery percentage              battery name (BAT0)
 *                                                     NULL on OpenBSD/FreeBSD
 * battery_remaining   battery remaining HH:MM         battery name (BAT0)
 *                                                     NULL on OpenBSD/FreeBSD
 * battery_state       battery charging state          battery name (BAT0)
 *                                                     NULL on OpenBSD/FreeBSD
 * cat                 read arbitrary file             path
 * cpu_freq            cpu frequency in MHz            NULL
 * cpu_perc            cpu usage in percent            NULL
 * datetime            date and time                   format string (%F %T)
 * disk_free           free disk space in GB           mountpoint path (/)
 * disk_perc           disk usage in percent           mountpoint path (/)
 * disk_total          total disk space in GB          mountpoint path (/)
 * disk_used           used disk space in GB           mountpoint path (/)
 * entropy             available entropy               NULL
 * gid                 GID of current user             NULL
 * hostname            hostname                        NULL
 * ipv4                IPv4 address                    interface name (eth0)
 * ipv6                IPv6 address                    interface name (eth0)
 * kernel_release      `uname -r`                      NULL
 * keyboard_indicators caps/num lock indicators        format string (c?n?)
 *                                                     see keyboard_indicators.c
 * keymap              layout (variant) of current     NULL
 *                     keymap
 * load_avg            load average                    NULL
 * netspeed_rx         receive network speed           interface name (wlan0)
 * netspeed_tx         transfer network speed          interface name (wlan0)
 * num_files           number of files in a directory  path
 *                                                     (/home/foo/Inbox/cur)
 * ram_free            free memory in GB               NULL
 * ram_perc            memory usage in percent         NULL
 * ram_total           total memory size in GB         NULL
 * ram_used            used memory in GB               NULL
 * run_command         custom shell command            command (echo foo)
 * swap_free           free swap in GB                 NULL
 * swap_perc           swap usage in percent           NULL
 * swap_total          total swap size in GB           NULL
 * swap_used           used swap in GB                 NULL
 * temp                temperature in degree celsius   sensor file
 *                                                     (/sys/class/thermal/...)
 *                                                     NULL on OpenBSD
 *                                                     thermal zone on FreeBSD
 *                                                     (tz0, tz1, etc.)
 * uid                 UID of current user             NULL
 * uptime              system uptime                   NULL
 * username            username of current user        NULL
 * vol_perc            OSS/ALSA volume in percent      mixer file (/dev/mixer)
 *                                                     NULL on OpenBSD/FreeBSD
 * wifi_essid          WiFi ESSID                      interface name (wlan0)
 * wifi_perc           WiFi signal in percent          interface name (wlan0)
 */

// Show wifi icons
static char wireless_interface[32] = "n/a"; // 全局变量，存储无线网卡名称

const char *get_wireless_interface(void) {
  FILE *fp;
  char line[256];

  // 打开/proc/net/wireless文件
  fp = fopen("/proc/net/wireless", "r");
  if (fp == NULL) {
    perror("Error opening file");
    return unknown_str; // 返回未知值
  }

  // 跳过前两行
  fgets(line, sizeof(line), fp);
  fgets(line, sizeof(line), fp);
  // 读取第三行，获取无线网卡名称
  if (fgets(line, sizeof(line), fp) != NULL) {
    // 提取无线网卡名称，去除前面的空格
    if (sscanf(line, " %[^:]", wireless_interface) != 1) {
      fprintf(stderr, "Error parsing interface name from line: %s", line);
      strcpy(wireless_interface, unknown_str);
    } else {
      // 去除字符串末尾的空格
      size_t len = strlen(wireless_interface);
      while (len > 0 && (wireless_interface[len - 1] == ' ' ||
                         wireless_interface[len - 1] == '\n')) {
        wireless_interface[len - 1] = '\0';
        len--;
      }
    }
  } else {
    fprintf(stderr, "Error reading third line\n");
    strcpy(wireless_interface, unknown_str);
  }

  fclose(fp);
  return wireless_interface;
}

// 构造函数，确保在 main 函数执行前调用
static void __attribute__((constructor)) init_wireless_interface(void) {
  get_wireless_interface();
}

// Show signal icons
static inline const char *get_wifi_icon_based_on_perc(const char *interface) {
  const char *perc_str = wifi_perc(interface);
  if (perc_str == NULL || perc_str[0] == '\0') {
    return "󰤭"; // WiFi 未连接
  }

  int perc = atoi(perc_str); // 将 wifi_perc 返回的百分比字符串转换为整数
  const char *icon = "";
  if (perc <= 0)
    icon = "󰤯";
  else if (perc <= 25)
    icon = "󰤟";
  else if (perc <= 50)
    icon = "󰤢";
  else if (perc <= 75)
    icon = "󰤥";
  else
    icon = "󰤨";
  return icon;
}

// Show volume icons
static const char vol[] =
    "muted=$(wpctl get-volume @DEFAULT_AUDIO_SINK@ | awk '{print $3;}'); \
     volume=$(wpctl get-volume @DEFAULT_AUDIO_SINK@ | awk '{print $2;}' | awk '{print $1 * 100}' | cut -d. -f1); \
     if [ -n \"${muted}\" ]; then \
         printf \"󰸈\"; \
     elif [ \"$volume\" -eq 0 ]; then \
         printf \"\"; \
     elif [ \"$volume\" -le 50 ]; then \
         printf \"\"; \
     elif [ \"$volume\" -le 99 ]; then \
         printf \"\"; \
     else \
         printf \"\"; \
     fi";

// Show mic icons
static const char mic[] =
    "muted=$(wpctl get-volume @DEFAULT_AUDIO_SOURCE@ | awk '{print $3;}'); \
     volume=$(wpctl get-volume @DEFAULT_AUDIO_SOURCE@ | awk '{print $2;}'); \
     if [ \"$muted\" ]; then \
         printf \" \"; \
     elif [ \"$volume\" = \"1.00\" ]; then \
         printf \" \"; \
     else \
         printf \"%.0f \" \"$volume\"; \
     fi";

// Show brightness icons
static const char *icons[] = {"󰛩", "󱩎", "󱩏", "󱩐", "󱩑", "󱩒",
                              "󱩓", "󱩔", "󱩕", "󱩖", "󰛨"};
static const char *error_icon = "󱧤"; // 定义一个默认图标表示错误或未知状态

static const char *get_brightness_icon() {
  FILE *pipe = popen(
      "brightnessctl g | awk '{print int($1 * 100 / 3000)}' | tr -d '\\n'",
      "r");
  if (!pipe) {
    perror("popen");
    return error_icon;
  }

  char buffer[128];
  if (fgets(buffer, sizeof(buffer), pipe) != NULL) {
    int brightness = atoi(buffer);
    pclose(pipe);
    if (brightness < 0)
      brightness = 0;
    if (brightness > 100)
      brightness = 100;
    int icon_index = brightness / 10;
    return icons[icon_index];
  }

  pclose(pipe);
  return error_icon;
}

// Show battery icons
static inline const char *
get_battery_icon_based_on_perc_and_state(const char *bat) {
  const char *perc_str = battery_perc(bat);
  const char *state_str = battery_state(bat);
  if (perc_str == NULL || perc_str[0] == '\0') {
    return "󰂑"; // 电池未检测到
  }

  int perc = atoi(perc_str); // 将 battery_perc 返回的百分比字符串转换为整数
  const char *icon = "";
  if (strcmp(state_str, "󱟤") == 0) { // 电池放电状态
    if (perc <= 10)
      icon = "󰁺";
    else if (perc <= 20)
      icon = "󰁻";
    else if (perc <= 30)
      icon = "󰁼";
    else if (perc <= 40)
      icon = "󰁽";
    else if (perc <= 50)
      icon = "󰁾";
    else if (perc <= 60)
      icon = "󰁿";
    else if (perc <= 70)
      icon = "󰂀";
    else if (perc <= 80)
      icon = "󰂁";
    else if (perc <= 90)
      icon = "󰂂";
    else
      icon = "󰁹";
  } else if (strcmp(state_str, "󱟦") == 0) { // 电池充电状态
    if (perc <= 10)
      icon = "󰢟";
    else if (perc <= 20)
      icon = "󰢜";
    else if (perc <= 30)
      icon = "󰂆";
    else if (perc <= 40)
      icon = "󰂇";
    else if (perc <= 50)
      icon = "󰂈";
    else if (perc <= 60)
      icon = "󰢝";
    else if (perc <= 70)
      icon = "󰂉";
    else if (perc <= 80)
      icon = "󰢞";
    else if (perc <= 90)
      icon = "󰂊";
    else
      icon = "󰂅";
  } else if (strcmp(state_str, "󱟢") == 0) { // 电池满电状态
    icon = "󰂄";
  } else { // 其他状态（如未充电等）
    icon = "󰚥";
  }
  return icon;
}

static const struct arg args[] = {
    /* function format          argument */
    {cpu_perc, " 󰍛%s", NULL},
    {ram_perc, " %s", NULL},
    {run_command, " %s", mic},
    {run_command, "%s", vol},
    {get_brightness_icon, " %s", NULL}, // 使用 get_brightness_icon 函数
    {get_battery_icon_based_on_perc_and_state, " %s", "BAT0"},
    {get_wifi_icon_based_on_perc, " %s", wireless_interface},
    //{wifi_perc, "%s", wireless_interface},
    {datetime, " %s", "%a %b %d %H:%M"},
};
