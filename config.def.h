/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>
static const char *upvolume[]  = {"pamixer", "-i", "5", NULL};
static const char *downvolume[]  = {"pamixer", "-d", "5", NULL};
static const char *mutevolume[]  = {"pamixer", "--toggle-mute", NULL};
static const char *mutemic[]  = {"amixer", "-qM", "sset", "Capture", "toggle", NULL};
/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const int startwithgaps[]      = { 1 };
static const unsigned int gappx[]    = { 1 };
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 1;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "FiraCode Nerd Font Mono:size=16" };
static const char dmenufont[]       = "FiraCode Nerd Font Mono:size=10";
static const char col_gray1[]       = "#100D23";
static const char col_gray2[]       = "#9E9E61";
static const char col_gray3[]       = "#9E619E";
static const char col_gray4[]       = "#619E9E";
static const char col_cyan[]        = "#372963";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, NULL },
	[SchemeSel]  = { col_gray4, col_cyan,  col_gray3  },
};

/* tagging */
static const char *tags[] = { "☰", "☱", "☲", "☳", "☴", "☵", "☶", "☷", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
	{ "Chromium",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "kitty", NULL };
static const char *chromium[] = { "chromium", NULL };
static const char *print_screen_cmd[] = { "scrot", "%Y-%m-%d-%H%M%S.png", "-e", "mv $f ~/Pictures/screenshots", NULL };
static const char *brightnessup[] = { "light", "-A", "5", NULL }; /* Fn + Home（此组合有唯一Keycode） 是Thinkpad x220的增加亮度 */
static const char *brightnessdown[] = { "light", "-U", "5", NULL }; /* Fn + End（此组合有唯一Keycode） 是Thinkpad x220的降低亮度 */
static const char *rofi[] = {"rofi", "-show", "drun", NULL };
static const char *powermenu[] = { "./.config/rofi/leave/powermenu.sh", NULL };
static const char *wifi_menu[] = { "./.config/rofi/wifi_menu/rofi_wifi_menu.sh", NULL };
static const char *htop[] = {"kitty", "htop", NULL };
static const Key keys[] = {
	/* modifier                     key        function        argument */
    { 0,                      0x1008ff41,      spawn,          {.v = chromium } },/* 将ThinkVantage键绑定为chromium浏览器，0x1008ff41为16进制keysym*/
    { 0,         XF86XK_AudioLowerVolume,      spawn,          {.v = downvolume } },
    { 0,         XF86XK_AudioRaiseVolume,      spawn,          {.v = upvolume } },
    { 0,                XF86XK_AudioMute,      spawn,          {.v = mutevolume } },
    { 0,             XF86XK_AudioMicMute,      spawn,          {.v = mutemic } },
    { 0,                        XK_Print,      spawn,          {.v = print_screen_cmd } },
    { 0,          XF86XK_MonBrightnessUp,      spawn,          {.v = brightnessup } },/* 系统默认增加亮度的KeySym*/
    { 0,        XF86XK_MonBrightnessDown,      spawn,          {.v = brightnessdown } },/* 系统默认降低亮度的KeySym*/
	{ MODKEY|ShiftMask,             XK_e, spawn,          {.v = powermenu } },
	{ MODKEY|ShiftMask,             XK_n, spawn,          {.v = wifi_menu } },
	{ MODKEY|ShiftMask,             XK_t, spawn,          {.v = htop } },
	{ MODKEY,                       XK_p,      spawn,          {.v = rofi } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
        { MODKEY,                       XK_minus,  setgaps,        {.i = -5 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +5 } },
	{ MODKEY|ShiftMask,             XK_minus,  setgaps,        {.i = GAP_RESET } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = GAP_TOGGLE } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

