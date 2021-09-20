09.12.2021 突然发现有人跟我用一样的laptop 装 arch linux 和 dwm https://gist.github.com/palopezv/efd34059af6126ad970940bcc6a90f2e
This is my DWM backup, version init
dwm/config.h里面记录了当前修改过的设置
已经打了alpha补丁（config.h 里面的代码只有keybinding有参考价值，其他的可能有误改或意外删除）
xmodmap用法：
假设要改modifier：mod3 改为 q
首先 创建文件 
xmodmap -pke > ~/.Xmodmap
然后
1. xmodmap -e "clear mod3"
2. xmodmap -e "add mod3 = q"
3. xmodmap ~./Xmodmap 
4. 修改 ~/.xinitrc 顶部加入 (sleep 15s && xmodmap ~/.Xmodmap) & 来延迟命令防止被其他命令覆盖

# 按需要安装的软件
vim (--with x compiled from source)
paru
pacman -S tlp iptables-nft ipset firewalled terminus-font efibootmgr iwd base-devel linux-headers xdg-user-dirs xdg-utils bluez bluez-utils pulseaudio-bluetooth alsa-utils acpi acpi_call you-get ranger ueberzug highlight mpv w3m atool poppler zip unzip-iconv unrar p7zip picom xorg xorg-xinit intel-ucode nitrogen chromium dialog xf86-video-intel wireguard fcitx5-im fcitx5-rime fcitx5-material-color scrot wqy-zenhei ttf-fireflysung otf-fira-code nerd-fonts-fire-code resolvconf(for wireguard) cmake(for YouCompleteMe) xpdf connman
# 针对DWM
1.dwm-bar
2.slock
3.dwm patches:
(1)dwm alpha
(2)dwm fullgap
(3)st alpha
(4)st scrollback
(5)st  w3m images
(6)dwm hide vacant tags
# 关于wireguard无法链接google
在client.conf里面：
1.MTU设置为1280，详见 https://yooooex.com/2019/05/23/wireguard-deploy/
2.添加 DNS = 8.8.8.8 (google)(但是不懂为什么每次重启都需要进wg0.conf设置一次然后重新wg-quick up wg0 {查到的原理：通过 DHCP 向客户端宣告 DNS 服务器。客户端将会使用这里指定的 DNS 服务器来处理 VPN 子网中的 DNS 请求，但也可以在系统中覆盖此选项。例如：

如果不配置则使用系统默认 DNS
可以指定单个 DNS：DNS = 1.1.1.1
也可以指定多个 DNS：DNS = 1.1.1.1,8.8.8.8}
//通过原理解决了，解决方案：更改系统默认dns：在/etc/resolve.conf 中添加两行：
nameserver 8.8.8.8
nameserver 8.8.4.4)(详见https://fuckcloudnative.io/posts/wireguard-docs-practice/ 以及 https://www.osyunwei.com/archives/2839.html)
解决wireguard在laptop休眠时断掉(我没有动因为好麻烦而且手动更灵活)：
https://www.reddit.com/r/WireGuard/comments/jdwb50/guide_wireguard_for_windows_and_linux_tunnel/
https://askubuntu.com/questions/1189178/systemd-resolve-reset-after-wake-from-suspend
https://bbs.archlinux.org/viewtopic.php?id=248843
11.09.2021
# DWM Status Bar
如果你用 xsetroot, 在loop中加入 xsetroot -name "$ status | tr '\n' ' '" //把newlines 替换成spaces来解决dwm变慢的问题
# Arch Linux
添加源
1./etc/pacman.d/mirrorlist (添加了中国国内源，韩国源因为vpc走韩国)
2./etc/pacman.conf （添加了中文社区仓库archlinuxcn）
#Ranger
zv: set use_preview_script! (for preview plain text)
# For Bluetooth headphones paired, but no sound after a while
https://forum.manjaro.org/t/howto-bluetooth-headphones-paired-but-no-sound-after-a-while/33141
