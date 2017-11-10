1. Run `sudo raspi-config`
    * update raspi-config
    * enable SSH
    * enable VNC
    * change hostname
    * update locale
    * keyboard
    * timezone
    * enable SPI
    * disable serial port
    * expand file system

1. Run `sudo dpkg-reconfigure console-setup` and select:

    * Encoding to use on the console: <UTF-8>
    * Character set to support: <Guess optimal character set>
    * Font for the console: Terminus (default is VGA)
    * Font size: 6x12 (framebuffer only)

1. Run `sudo apt-get update` then `sudo apt-get upgrade`

1. Run `sudo apt-get install vim unclutter atool`
    * unclutter - will be used to hide the cursor when running with the LCD
    * atool - is a nice tool to unzip files with

1. Setup passwordless ssh `vi ~/.ssh/authorized_keys` (copy key from local `~/.ssh/id_rsa.pub`)

1. Setup Wifi
  1. `sudo iwlist wlan0 scan`
  1. `sudo vi /etc/wpa_supplicant/wpa_supplicant.conf` and add
  
         network={
             ssid="testing"
             psk="testingPassword"
         }

1. Install newer version of node
  1. Uninstall old node `sudo apt-get remove nodejs npm node-semver`

  1. Install a newer node

         wget https://nodejs.org/dist/v8.9.1/node-v8.9.1-linux-armv7l.tar.xz
         aunpack node-v8.9.1-linux-armv7l.tar.xz
         sudo mv node-v8.9.1-linux-armv7l /opt/
         rm node-v8.9.1-linux-armv7l.tar.xz
         sudo ln -s /opt/node-v8.9.1-linux-armv7l /opt/node
         sudo rm /usr/bin/node
         sudo ln -s /opt/node/bin/node /usr/bin/node
         sudo ln -s /opt/node/bin/npm /usr/bin/npm
  
1. Enable the display
  1. Append the following to `/boot/config.txt`
  
         gpu_mem=256
         dtoverlay=tinylcd35,rotate=270,speed=48000000,touch
         dtoverlay=pi3-miniuart-bt
  
  1. Create a file `/usr/share/X11/xorg.conf.d/99-calibration.conf` with:
  
         Section "InputClass"
           Identifier "calibration"
           MatchProduct "ADS7846 Touchscreen"
           Option "Calibration" "3911 99 121 3858"
           Option "InvertX" "1"
           Option "InvertY" "1"
           Option "TransformationMatrix" "0 1 0 -1 0 1 0 0 1"
         EndSection
        
  1. Create a file `/usr/share/X11/xorg.conf.d/99-fbdev.conf`
  
         Section "Device"  
           Identifier "myfb"
           Driver "fbdev"
           Option "fbdev" "/dev/fb1"
         EndSection

1. Add `fbcon=map:10 consoleblank=0` to the end of the line in `/boot/cmdline.txt`
   * fbcon - enable the LCD as a console display
   * consoleblank - disable screen blanking in console

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

1. Install Google Assistant by following these instructions: https://developers.google.com/assistant/sdk/develop/python/

1. Install the server

       git clone https://github.com/joeferner/alarm-clock.git
       cd ~/alarm-clock/server/src
       npm install
       cd ~/alarm-clock/server/web/src
       npm install
       cd ~/alarm-clock/web
       sudo mkdir /var/log/alarm-clock
       sudo chown pi:pi /var/log/alarm-clock
       # update /home/pi/alarm-clock/server/src/settings.json

# Enable Audio

1. Find USB audio `aplay -l` and `arecord -l`
1. Create file `~/.asoundrc` replacing card number and device number (probably 0)

       pcm.!default {
         type asym
         capture.pcm "mic"
         playback.pcm "speaker"
       }
       pcm.mic {
         type plug
         slave {
           pcm "hw:<card number>,<device number>"
         }
       }
       pcm.speaker {
         type plug
         slave {
           pcm "hw:<card number>,<device number>"
         }
       }
