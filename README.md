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

# Archliunx 按需要安装的软件  
vim (--with x compiled from source)  
paru： `git clone https://aur.archlinux.org/paru.git` ,then `cd paru-bin` `makepkg -si`

```
pacman -S 

tlp iptables-nft ipset clash proxychains-ng

efibootmgr iwd base-devel linux-headers

bluez bluez-utils pulseaudio-bluetooth alsa-utils acpi acpi_call 

you-get ranger ueberzug highlight mpv w3m atool poppler zip unzip rar p7zip 

picom-jonaburg-git xorg-xprop xorg xorg-xinit intel-ucode nitrogen chromium dialog xf86-video-intel 

fcitx5-im fcitx5-rime fcitx5-material-color scrot 

wqy-zenhei otf-nerd-fonts-fira-code otf-font-awesome 

fish <starship oh-my-fish>(这两个从github下载）wireguard resolvconf(for wireguard) cmake(for YouCompleteMe) xpdf connman 

ntfs-3g(使windows-linux u盘文件格式可以共通https://segmentfault.com/a/1190000016491615 ）

surf webkit2gtk gcr(these two for surf) sl dash checkbashisms(these two for relink /bin/sh to dash 4 times faster than bash)

sxiv(image viewer)

```
# DWM 安装的一些插件  
```
dwm software:
1.dwm-bar 
2.slocks

dwm patches:  
(1)dwm-alpha  
(2)dwm-fuctionalgaps+pertag  
(3)dwm-hide_vacant_tags  
(4)st-alpha  
(5)st-scrollback  
(6)st-w3m  
(7)st-hidecursor  
(8)st-anysize
```
# 安装expac并按日期查询

用 expac 查询最近安装的 20 个软件包：
`expac --timefmt='%Y-%m-%d %T' '%l\t%n' | sort | tail -n 20`

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
> `battery.c` 和 `slstatus` 这两个都是slstatus status-bar的部分改动过的配置文件

> .xpdfrc 为 xpdf的个人配置文件

> picom.conf is config file for picom-jonaburg-git


# 科学上网：

## clash on archlinux

https://blog.linioi.com/posts/clash-on-arch/ 

https://kb.kywiki.xyz/linux2.html

设定代理规则：clash通过Razord面板实现：http://clash.razord.top/#/proxies

put these in .bashrc in order to toggle proxy in specific terminal for such as updating neovim packer:

```
alias sp='export http_proxy="127.0.0.1:7890";export https_proxy="127.0.0.1:7890";export socks_proxy="127.0.0.1:7891";'
alias usp='unset http_proxy; unset https_proxy; unset socks_proxy;'
```

## clash on Windows 10, wsl2 config:

wsl2 + archlinux + clash .bashrc toggle proxy setting: 

sp: virtual ip env0 proxy up
usp: virtual ip env0 proxy down

```
hostip=$(cat /etc/resolv.conf |grep -oP '(?<=nameserver\s).*')
alias sp='export https_proxy="http://${hostip}:7890";export http_proxy="http://${hostip}:7890";export all_proxy="socks5://${hostip}:7890";export ALL_PROXY="socks5://${hostip}:7890";'
alias usp='unset https_proxy; unset http_proxy; unset all_proxy; unset ALL_PROXY;'
```

# 安裝ArchLinux時選擇 brtfs 文件系統 & systemd-boot
要在arch.conf 的 `options` 里加入一句 `rootflags=subvol=@`, 同時，mkinitcpio.conf 的 `module()`里也加入 `brtfs`

https://arch.icekylin.online/

https://bbs.archlinux.org/viewtopic.php?id=267207



# Graphic Drivers

     > Nvidia
     > 前往 https://www.nvidia.com/en-us/drivers/unix/legacy-gpu/ 查看 Nvidia 私有驱动最新版本不支持的显卡列表，如果你的显卡不在这个列表里，那么你可以使用最新的 Nvidia 私有驱动，反之则需要使用开源驱动或旧版私有驱动（通过 AUR 安装）。
     > 
     > 最新私有驱动：sudo pacman -S nvidia nvidia-settings cuda xorg-server-devel lib32-nvidia-utils lib32-opencl-nvidia
     > 
     > 最新私有驱动的 OpenCL: sudo pacman -S opencl-nvidia ocl-icd
     > 
     > 开源驱动：sudo pacman -S mesa mesa-vdpau libva-mesa-driver lib32-mesa lib32-mesa-vdpau lib32-libva-mesa-driver
     > 
     > 某些 Nvidia 显卡型号使用开源驱动可能无法完全发挥性能，或者某些功能无法正常工作。
     >
     > AMD
     >（GCN 1 and above）：sudo pacman -S mesa mesa-vdpau libva-mesa-driver lib32-mesa lib32-mesa-vdpau lib32-libva-mesa-driver lib32-opencl-mesa
     > 
     >（TeraScale 1 2 3 framework）：sudo pacman -S mesa mesa-vdpau libva-mesa-driver lib32-mesa lib32-mesa-vdpau lib32-libva-mesa-driver lib32-opencl-mesa
     > 
     > Vulkan：sudo pacman -S vulkan-icd-loader vulkan-radeon lib32-vulkan-icd-loader lib32-vulkan-radeon
     > 
     > OpenCL: sudo pacman -S opencl-mesa ocl-icd
     > 
     > andvlk 是由 AMD 开源的 AMD GPU Vulkan 实现，这个实现比 Mesa 的 RADV 在某些场景下性能要好一些，并且系统允许安装多个 Vulkan 实现并让软件进行选择，推荐游戏玩家安装。
     > 
     > Intel
     > Driver：sudo pacman -S mesa vulkan-icd-loader vulkan-intel lib32-mesa lib32-vulkan-icd-loader lib32-vulkan-intel
     > 
     > 硬件视频加速：如果你的 Intel CPU 架构是 Broadwell 或以上的安装intel-media-driver，反之则安装libva-intel-driver lib32-libva-intel-driver。
     > 
     > OpenCL：如果你的 Intel CPU 架构是 Broadwell 或以上的安装intel-compute-runtime ocl-icd，反之则安装beignet ocl-icd，beignet 需要通过 AUR 安装。
     > Linux LVM学习总结——Insufficient Free Extents for a Logical Volume: https://www.cnblogs.com/kerrycode/p/9745060.html
     > 系统分区时用ssd给机械硬盘加速技术lvmcache 
     > https://www.lovelycxy.com/h/en0KJQB8c1Q.html
     > https://www.cnblogs.com/jfLin/p/9542812.html
     
luna_pinyin.sogou.dict.yaml：给fcitx5-rime输入法加入搜狗标准词库

luna_pinyin.sogoun.dict.yaml：给fcitx5-rime输入法加入搜狗网络词库

Archlinux in windows subsystem for linux:
error: https://github.com/DDoSolitary/LxRunOffline/issues/171
