## MySysInfo - system monitor for Linux

# Installation

## Build

Download the latest version using git clone command:

```bash
git clone git://github.com/christmaaas/MySysInfo.git
```

Change to the MySysInfo source directory:

```
cd MySysInfo
```

and launch 'make' utility to compile MySysInfo in debug mode:

```
make MODE=debug
```

Or to compile MySysInfo in release mode:

```
make MODE=release
```

If compilation was successful, an bin directory will be created in the current directory.
Change to the bin directory:

```
cd bin
```

You can now launch MySysInfo by typing ```./{debug|release}```. 

# Uninstall

Remove MySysInfo source direcotry:

```bash
rm -rf MySysInfo
```

# Usage Examples

## Launch MySysInfo Ncurses mode

```
./{debug|release}
```

## Show "Help" information

* Add the following row to your cron schedule:

```
./{debug|release} -h
```
