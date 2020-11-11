#!/bin/bash
set -ev

date
# Don't update to use included Qt version instead of Qt 5.15.x
export HOMEBREW_NO_AUTO_UPDATE=1
export HOMEBREW_NO_INSTALL_CLEANUP=1

brew unlink python@2 # to avoid conflicts with qt/libical dependence on python

#brew upgrade qt5 # to get 5.15.x
/usr/local/opt/qt5/bin/qmake --version

brew install gsl
brew install libical
brew upgrade libusb
brew install srmio
brew install libsamplerate
rm -rf '/usr/local/include/c++'
brew install r
## Disable KML for now
## brew install --HEAD travis/libkml.rb
sudo chmod -R +w /usr/local

# D2XX - refresh cache if folder is empty
if [ -z "$(ls -A D2XX)" ]; then
    curl -O https://www.ftdichip.com/Drivers/D2XX/MacOSX/D2XX1.2.2.dmg
    hdiutil mount D2XX1.2.2.dmg
    cp /Volumes/release/D2XX/Object/10.5-10.7/x86_64/libftd2xx.1.2.2.dylib D2XX
    cp /Volumes/release/D2XX/bin/*.h D2XX
fi
sudo cp D2XX/libftd2xx.1.2.2.dylib /usr/local/lib

# VLC
if [[ -z "$(ls -A VLC)" ]]; then
    curl -O http://download.videolan.org/pub/videolan/vlc/3.0.8/macosx/vlc-3.0.8.dmg
    hdiutil mount vlc-3.0.8.dmg
    cp -R "/Volumes/VLC media player/VLC.app/Contents/MacOS/include" VLC/include
    cp -R "/Volumes/VLC media player/VLC.app/Contents/MacOS/lib" VLC/lib
    cp -R "/Volumes/VLC media player/VLC.app/Contents/MacOS/plugins" VLC/plugins
    rm -f VLC/plugins/plugins.dat
fi
sudo cp VLC/lib/libvlc*.dylib /usr/local/lib

# AWS client to upload binaries to S3 bucket
brew install awscli
aws --version

exit
