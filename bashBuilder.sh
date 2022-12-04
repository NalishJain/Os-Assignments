#! /bin/bash
mkdir /home/kernelbuild1
cd /home/kernelbuild1
wget -P /home/kernelbuild1/ https://cdn.kernel.org/pub/linux/kernel/v5.x/linux-5.19.17.tar.xz
unxz linux-5.19.17.tar.xz 
tar -xvf linux-5.19.17.tar
chown -R $USER:$USER linux-5.19.17