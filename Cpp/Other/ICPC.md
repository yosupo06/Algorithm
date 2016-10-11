# 環境

Ubuntu 16.04 64bitと仮定

使用エディタはgedit


# gedit

Edit -> Preferenceから各種設定
- Display line numbers
- Highlight current line
- Highlight matching branckets
- Tabwidth:4
- Auto Indent

# Unity

各種キーバーインドがemacs"風"になる。チームメイトと要相談、だけど無いとポンコツになる

~/.profileへ

gsettings set org.gnome.desktop.interface gtk-key-theme Emacs
setxkbmap -option ctrl:nocaps
setxkbmap -option ctrl:nosuper
