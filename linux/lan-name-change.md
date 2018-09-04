- ubuntu16.04修改网卡名称
> sudo nano /etc/default/grub
- 找到GRUB_CMDLINE_LINUX=""
- 改为GRUB_CMDLINE_LINUX="net.ifnames=0 biosdevname=0"
- 然后sudo grub-mkconfig -o /boot/grub/grub.cfg
