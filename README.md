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
