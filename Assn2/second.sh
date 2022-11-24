mkdir kernelbuild-2
mkdir kernelbuild-3
cp -R kernelbuild-1 kernelbuild-2
cp -R kernelbuild-1 kernelbuild-3
cd /root/kernelbuild-1/linux-5.15.79
make mrproper
cd /root/kernelbuild-2/kernelbuild-1/linux-5.15.79
make mrproper
cd /root/kernelbuild-3/kernelbuild-1/linux-5.15.79
make mrproper
