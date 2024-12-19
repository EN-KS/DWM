# !/bin/sh(from xorg-xinit)
export LANG=en_US.UTF-8
## export LANGUAGE=zh_CN:en_US
#userresources=$HOME/.Xresources
#usermodmap=$HOME/.Xmodmap
#sysresources=/etc/X11/xinit/.Xresources
#sysmodmap=/etc/X11/xinit/.Xmodmap

setxkbmap -option ctrl:swapcaps

## merge in defaults and keymaps
#if [ -f $sysresources ]; then
#
#
#
#
#
#
#
#    xrdb -merge $sysresources
#
#fi
#
#
#if [ -f $sysmodmap ]; then
#    xmodmap $sysmodmap
#fi
#
#if [ -f "$userresources" ]; then
#
#
#
#
#
#
#
#    xrdb -merge "$userresources"
#
#fi
#
#if [ -f "$usermodmap" ]; then
#    xmodmap "$usermodmap"
#fi
#
## start some nice programs
#
#if [ -d /etc/X11/xinit/xinitrc.d ] ; then
# for f in /etc/X11/xinit/xinitrc.d/?*.sh ; do
#  [ -x "$f" ] && . "$f"
# done
# unset f
#fi
#
#
#
## fcitx5
export GTK_IM_MODULE=fcitx5
export QT_IM_MODULE=fcitx5
export XMODIFIERS="@im=fcitx5"
export INPUT_METHOD=fcitx
export SDL_IM_MODULE=fcitx
export GLFW_IM_MODULE=ibus
fcitx5 &


# Wallpaper
nitrogen --force-setter=xinerama --restore -b

# IDEA
#export _JAVA_AWT_WM_NONREPARENTING=1

# DWM Status
slstatus &

# Compositor
picom -b

gnome_schema="org.gnome.desktop.interface"
gsettings set "$gnome_schema" gtk-theme "Catppuccin-blue"
gsettings set "$gnome_schema" icon-theme "Papirus-Dark"
/usr/lib/polkit-gnome/polkit-gnome-authentication-agent-1 &
#nm-applet &
dunst -config ~/.config/dunst/dunstrc &

# Loop
#while true; do
#	dwm >/dev/null 2>&1
#done


# Execute DWM
exec dwm
