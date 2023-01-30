#
# ~/.bash_profile
#
export EDITOR='nvim'

# java_home and java path
export WORKSPACE=$HOME/.config/nvim/workspace/ # 不设置则默认是$HOME/workspace
#export JAVA_HOME=/usr/lib/jvm/java-17-openjdk
#PATH=$PATH:$JAVA_HOME/bin
#export JDTLS_HOME=$HOME/.config/nvim/jdtls/ # 包含 plugin 和 configs 的目录，由jdt-language-server-xxx.tar.gz解压出的

# Go 环境变量设置
export GOROOT=/usr/lib/go # go语言安装目录
export GOPATH=~/Projects/go # go语言工作区
export GOBIN=$GOPATH/bin # 存放go语言可执行文件目录
export PATH=$PATH:$GOROOT/bin:$GOBIN # 为了随地调用go语言命令和go编译后的可执行文件，可以将$GOROOT/bin和$GOBIN加入到PATH

#lf Change working dir in shell to last dir in lf on exit
lfcd () {
    tmp="$(mktemp)"
    lf -last-dir-path="$tmp" "$@"
    if [ -f "$tmp" ]; then
        dir="$(cat "$tmp")"
        rm -f "$tmp"
        if [ -d "$dir" ]; then
            if [ "$dir" != "$(pwd)" ]; then
                cd "$dir"
            fi
        fi
    fi
}
bind '"\C-o":"lfcd\C-m"'

# autostart X at login
if [ -z "${DISPLAY}" ] && [ "${XDG_VTNR}" -eq 1 ]; then
  exec startx
fi

# bash-completion
if [ -f /etc/bash_completion ]; then
. /etc/bash_completion
fi

# QT5 FIX
export QT_QPA_PLATFORMTHEME="qt5ct"
# Wayland Fix
#export QT_QPA_PLATFORM="wayland;xcb"
#export XDG_CURRENT_DESKTOP=river
#export XDG_SESSION_DESKTOP=river
#export XDG_CURRENT_SESION_TYPE=wayland
#export GDK_BACKEND="wayland,x11"
#export MOZ_ENABLE_WAYLAND=1

[[ -f ~/.bashrc ]] && . ~/.bashrc
echo 't' | sudo -S systemctl start bluetooth
