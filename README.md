build&flash:
./util/docker_build.sh bastardkb/charybdis/3x5/v2/splinky_3:rj && while ! grep -q -s "/run/media/$USER/RPI-RP2" /proc/mounts; do sleep 1; done; echo doing the thing; cp ./bastardkb_charybdis_3x5_v2_splinky_3_rj.uf2 /run/media/RPI-RP2
