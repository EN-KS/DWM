Sep.12.2021  
突然发现有人跟我用一样的laptop 装 arch linux 和 dwm  
https://gist.github.com/palopezv/efd34059af6126ad970940bcc6a90f2e  

This is my DWM backup, version init  

dwm/config.h里面记录了当前修改过的设置  

已经打了alpha补丁 

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
paru： `git clone https://aur.archlinux.org/paru.git` ,then `cd paru-bin` `makepkg -si`

```
pacman -S 

tlp iptables-nft ipset terminus-font 

efibootmgr iwd base-devel linux-headers xdg-user-dirs xdg-utils 

bluez bluez-utils pulseaudio-bluetooth alsa-utils acpi acpi_call 

you-get ranger ueberzug highlight mpv w3m atool poppler zip unzip unrar p7zip 

picom-jonaburg-git xorg-xprop xorg xorg-xinit intel-ucode nitrogen chromium dialog xf86-video-intel 

wireguard fcitx5-im fcitx5-rime fcitx5-material-color scrot 

wqy-zenhei ttf-fireflysung resolvconf(for wireguard) cmake(for YouCompleteMe) xpdf connman 

powerline-console-fonts fish <starship oh-my-fish>(这两个从github下载）

ntfs-3g(使windows-linux u盘文件格式可以共通https://segmentfault.com/a/1190000016491615 ）

surf webkit2gtk gcr(these two for surf) sl dash checkbashisms(these two for relink /bin/sh to dash 4 times faster than bash)

sxiv(image viewer)

```
# 针对DWM  
1.dwm-bar  
2.slock  
3.dwm patches:  
(1)dwm-alpha  
(2)dwm-fuctionalgaps+pertag  
(3)dwm-hide_vacant_tags  
(4)st-alpha  
(5)st-scrollback  
(6)st-w3m  
(7)st-hidecursor  
(8)st-anysize  
# 关于wireguard无法链接google  
(wireguard 要先启动resolve才不会报错)  
  
```
systemctl enable systemd-resolved.service
```

wireguard 在client.conf里面： 
1.MTU设置为1280，详见 https://yooooex.com/2019/05/23/wireguard-deploy/  
2.添加 DNS = 8.8.8.8 (google)
(但是不懂为什么每次重启都需要进wg0.conf设置一次然后重新wg-quick up wg0 {查到的原理：通过 DHCP 向客户端宣告 DNS 服务器。客户端将会使用这里指定的 DNS 服务器来处理 VPN 子网中的 DNS 请求，但也可以在系统中覆盖此选项。例如： 
如果不配置则使用系统默认 DNS  
可以指定单个 DNS：DNS = 1.1.1.1  
也可以指定多个 DNS：DNS = 1.1.1.1,8.8.8.8}  
//通过原理解决了，解决方案：更改系统默认dns：在/etc/resolve.conf 中添加两行： 
nameserver 8.8.8.8  
nameserver 8.8.4.4)  
(详见https://fuckcloudnative.io/posts/wireguard-docs-practice/ 以及 https://www.osyunwei.com/archives/2839.html)  
解决wireguard在laptop休眠时断掉(我没有动因为好麻烦而且手动更灵活)： 
https://www.reddit.com/r/WireGuard/comments/jdwb50/guide_wireguard_for_windows_and_linux_tunnel/  
https://askubuntu.com/questions/1189178/systemd-resolve-reset-after-wake-from-suspend  
https://bbs.archlinux.org/viewtopic.php?id=248843  

Nov.09.2021  
# DWM Status Bar
如果你用 xsetroot, 在loop中加入 ```xsetroot -name "$ status | tr '\n' ' '"``` //把newlines 替换成spaces来解决dwm变慢的问题
# Arch Linux
添加源  
1./etc/pacman.d/mirrorlist (添加了中国国内源，韩国源因为vpc走韩国)  
2./etc/pacman.conf （添加了中文社区仓库archlinuxcn） 
#Ranger
zv: set use_preview_script! (for preview plain text)
# For Bluetooth headphones paired, but no sound after a while
https://forum.manjaro.org/t/howto-bluetooth-headphones-paired-but-no-sound-after-a-while/33141  

# Screen and External keyboard keymaps
//screen:  
```xrandr --output DP1 --mode 1920x1080 --output LVDS1 --mode 1366x768 --below DP1```

//keymap:  
```
setxkbmap -model pc104 -layout halmak_no_qwerty -option ctrl:swapcaps

```
Feb.18.2022  
# Arch linux -Syyu更新时遇到这个问题  
```
error: jansson: signature from "Eli Schwartz <eschwartz@archlinux.org>" is marginal trust       
:: File /var/cache/pacman/pkg/jansson-2.10-3-x86_64.pkg.tar.xz is corrupted (invalid or corrupted package (PGP signature)).
```
This should solve this problem:  
That means that the package integrity cannot be checked by its PGP signature. Often the reason is that you may have done the previous update a while ago. In the meantime some keys by Arch developers may have changed, and some new updates are signed with the new (PGP) keys.

Please try by updating the keyring first:
```
pacman -Sy archlinux-keyring
then try again

pacman -Syu
```
And let us know. Prefix the commands with sudo if you are using a user (non-root) shell.
  ```
  pacman-key --init
  pacman-key --populate archlinux
  ```
  
# pacman安装paru时出现ssl证书错误

解决办法：https://www.cnblogs.com/james-wangx/p/16111521.html `sudo timedatectl set-ntp true`


# 用ntfs-3g 格式化u盘为ntfs格式的命令  
```
sudo pacman -S ntfs-3g
sudo mkfs.ntfs -Q -L labelname /dev/设备名称
```
# `battery.c` 和 `slstatus`
这两个都是slstatus status-bar的部分改动过的配置文件

# .xpdfrc 为 xpdf的个人配置文件
# picom.conf is config file for picom-jonaburg-git


#科学上网：https://blog.linioi.com/posts/clash-on-arch/
