#!/bin/bash
# Aden Hilderbrand
# Josiah McNeely
# CI201 
# Section 01PC
# 
# series of menus and sub-menus to execute a number of linux sysadmin cli functions

######### functions ########

#functions directly from mainmenu
disk_menu () {
	echo "disk_menu "	
}
file_menu () {
	echo "file_menu "	
}
network_menu () {
	echo "network_menu "	
}
process_menu () {
	echo "process_menu "	
}
user_menu () {
	echo "user_menu "	
}
util_menu () {
	echo "util_menu "	
}

#### disk management functions ####
device_info () {
	echo "device_info "	
}
part_info () {
	echo "part_info "	
}
block_info () {
	echo "block_info "	
}
mount_info () {
	echo "mount_info"
}

#### file management functions ####
present_working_dir () {
	echo "present_working_dir"
}
list_dir_contents () {
	echo "list_dir_contents"
}
create_file () {
	echo "create_file"
}
change_file_perm () {
	echo "change_file_perm"
}
remove_file () {
	echo "remove_file"
}
read_file () {
	echo "read_file"
}

#### Network management functions ####
ip_info () {
	echo "ip_info"
}
ping_info () {
	echo "ping_info"
}
trace_route () {
	echo "trace_route"
}

#functions end

#mainmenu
main_menu () {
	echo "mainmenu"	
}

#### global , what runs first ####
main_menu()
