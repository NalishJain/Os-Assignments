cd /home/kernelbuild1/linux-5.19.17
wget -P /home/kernelbuild1/linux-5.19.17 --no-check-certificate 'https://docs.google.com/uc?export=download&id=15wIy6KDTNTQ9zgok2mOErfGn8QsSvGZ3' -O .config
make -j2
