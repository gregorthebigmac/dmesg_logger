# dmesg_logger
A service which will be executed upon boot and will output demsg to a sequential list of files once per second for five minutes.

## Why is this a thing?
This is specific to an issue I was having on an Ubuntu machine which was freezing/hanging just seconds after booting up. I didn't even have enough time to login before it would occur. I created this, removed the drive from the machine and mounted it on another machine as an external drive, placed the program inside, and modified crontab to load this program as soon as it boots.
