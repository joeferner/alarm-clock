1. Add chromium repositories

      wget -qO - http://bintray.com/user/downloadSubjectPublicKey?username=bintray | sudo apt-key add -
      echo "deb http://dl.bintray.com/kusti8/chromium-rpi jessie main" | sudo tee -a /etc/apt/sources.list

1. Run `sudo apt-get update` then `sudo apt-get upgrade`

1. Setup passwordless ssh `vi ~/.ssh/authorized_keys`

1. Install chromium `sudo apt-get install chromium-browser`

1. Install node `sudo apt-get install nodejs npm node-semver`

1. Install unclutter (hide cursor) `sudo apt-get install unclutter`

1. Install a newer node

      wget https://nodejs.org/dist/v6.2.0/node-v6.2.0-linux-armv7l.tar.xz
      tar xf node-v6.2.0-linux-armv7l.tar.xz
      sudo mv node-v6.2.0-linux-armv7l /opt/
      rm node-v6.2.0-linux-armv7l.tar.xz
      sudo ln -s /opt/node-v6.2.0-linux-armv7l /opt/node
      sudo rm /usr/bin/node
      sudo ln -s /opt/node-v6.2.0-linux-armv7l/bin/node /usr/bin/node

1. Run `sudo raspi-config` and update locale, keyboard, and timezone.

1. Run `sudo dpkg-reconfigure console-setup` and select:

    * Encoding to use on the console: <UTF-8>
    * Character set to support: <Guess optimal character set>
    * Font for the console: Terminus (default is VGA)
    * Font size: 6x12 (framebuffer only)

1. Add `fbcon=map:10 consoleblank=0` to the end of the line in `/boot/cmdline.txt`

1. Update `/etc/kbd/config` with `BLANK_TIME=0`
  
1. Append the following to `/boot/config.txt`

      gpu_mem=256
      dtparam=spi=on
      dtoverlay=tinylcd35,rotate=270,speed=48000000,touch

1. Create a file `/usr/share/X11/xorg.conf.d/99-calibration.conf` with:

      Section "InputClass"
        Identifier "calibration"
        MatchProduct "ADS7846 Touchscreen"
        Option "Calibration" "3911 99 121 3858"
        Option "SwapAxes" "1"
        Option "InvertX" "1"
        Option "InvertY" "1"
      EndSection
      
1. Create a file `/usr/share/X11/xorg.conf.d/99-fbdev.conf`

      Section "Device"  
        Identifier "myfb"
        Driver "fbdev"
        Option "fbdev" "/dev/fb1"
      EndSection

1. Edit `~/.config/lxsession/LXDE-pi/autostart`.

      #@lxpanel --profile LXDE-pi
      #@pcmanfm --desktop --profile LXDE-pi
      #@xscreensaver -no-splash
      @xset s off
      @xset -dpms
      @xset s noblank
      @unclutter
      @/home/pi/alarm-clock/server/start.sh
      @sed -i 's/"exited_cleanly": false/"exited_cleanly": true/' ~/.config/chromium/Default/Preferences
      @chromium-browser --noerrdialogs --kiosk http://localhost:8080

1. Install the server

      sudo npm install tsc tsd nodemon -g
      git clone alarm-clock
      cd server
      npm install
      tsd install
      tsc -w
      nodemon build/index.js
