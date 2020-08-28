#!/bin/bash

####################
# Lab 1 Exercise 4
# Name: Darien Chong
# Student No: A0168214H
# Lab Group: 6
####################

# fill the below up
hostname=$(uname -n)
kernel_version=$(uname -r)
process_cnt=$(ps -e | awk 'END {print NR}')
user_process_cnt=$(ps -u | awk 'END {print NR}')
mem_usage=$(free -b | awk 'NR==2, NR==3 {print ($2 == 0 ? 0 : $3/$2 * 100)}' | awk 'NR == 1 {print}')
swap_usage=$(free -b | awk 'NR==2, NR==3 {print ($2 == 0 ? 0 : $3/$2 * 100)}' | awk 'NR == 2 {print}')

echo "Hostname: $hostname"
echo "Linux Kernel Version: $kernel_version"
echo "Total Processes: $process_cnt"
echo "User Processes: $user_process_cnt"
echo "Memory Used (%): $mem_usage"
echo "Swap Used (%): $swap_usage"
