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
pacman -S tlp iptables-nft ipset firewalled terminus-font efibootmgr iwd base-devel linux-headers xdg-user-dirs xdg-utils bluez bluez-utils alsa-utils acpi acpi_call you-get ranger w3m picom xorg xorg-xinit intel-ucode nitrogen chromium dialog xf86-video-intel wireguard fcitx5-im fcitx5-rime fcitx5-material-color scrot wqy-zenhei ttf-fireflysung otf-fira-code resolvconf(for wireguard)

# 针对DWM
1.dwmstatus
2.slock
3.dwm patches:
(1)dwm alpha
(2)dwm fullgap
(3)st alpha
(4)st scrollback

# 关于wireguard无法链接google
在client.conf里面：
1.MTU设置为1280，详见 https://yooooex.com/2019/05/23/wireguard-deploy/
2.添加 DNS = 8.8.8.8 (google)(但是不懂为什么每次重启都需要进wg0.conf设置一次然后重新wg-quick up wg0 *解决方案：更改系统默认dns：在/etc/resolve.conf 中添加两行：
nameserver 8.8.8.8
nameserver 8.8.4.4)
