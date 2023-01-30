#
# ~/.bashrc
#

# If not running interactively, don't do anything

#archlinux
#alias sp='export http_proxy="127.0.0.1:7890";export https_proxy="127.0.0.1:7890";export socks_proxy="127.0.0.1:7891";'
#alias usp='unset http_proxy; unset https_proxy; unset socks_proxy;'

#archlinux in wsl
#alias sp='export https_proxy="http://${hostip}:7890";export http_proxy="http://${hostip}:7890";export all_proxy="socks5://${hostip}:7890";export ALL_PROXY="socks5://${hostip}:7890";'
#alias usp='unset https_proxy; unset http_proxy; unset all_proxy; unset ALL_PROXY;'

[[ $- != *i* ]] && return
alias v='nvim'
alias r='ranger'
alias ls='ls --color=auto'
alias x='startx'
PS1='[\u@\h \W]\$ '
#setxkbmap -model pc104 -layout us -option ctrl:swapcaps
#[ -f ~/.fzf.bash ] && source ~/.fzf.bash
eval "$(starship init bash)"
