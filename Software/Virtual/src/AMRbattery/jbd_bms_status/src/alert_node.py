#!/usr/bin/env python

import rospy
import os

from jbd_bms_msg.msg import JbdStatus

battery_yellow_warning = 55
battery_red_warning = 10

yellow_warning_b1 = False
red_warning_b1 = False
yellow_warning_b2 = False
red_warning_b2 = False

battery_past_value_b1 = 0
battery_present_value_b1 = 0
delta_b1 = 0

battery_past_value_b2 = 0
battery_present_value_b2 = 0
delta_b2 = 0

def callback1(msg):
	global battery_present_value_b1
	global yellow_warning_b1
	global red_warning_b1
	battlevel_b1=msg.Rsoc
	#print("Battery 1 level %s" %battlevel_b1)
	battery_past_value_b1 = battery_present_value_b1
	battery_present_value_b1 = battlevel_b1
	delta_b1 = battery_present_value_b1 - battery_past_value_b1

	if (delta_b1 != battery_present_value_b1):
		if (delta_b1 > 0):
			print("Battery charging")
			yellow_warning_b1 = False
			red_warning_b1 = False
		elif (delta_b1 < 0):
			print("Battery discharging")
		
		if (battery_past_value_b1 > 97):
			print("Battery fully charged!")

	if (battlevel_b1 < battery_yellow_warning) and (yellow_warning_b1 == False):
		print("Yo be careful. Battery 1 will die in the future")
		# Yellow warning has been displayed
		yellow_warning_b1 = True

	if (battlevel_b1 < battery_red_warning) and (red_warning_b1 == False):
		print("Yo be even more careful. Battery 1 dying")
		# Red warning has been displayed
		red_warning_b1 = True
		

def callback2(msg):
	global battery_present_value_b2
	global yellow_warning_b2
	global red_warning_b2
	battlevel_b2=msg.Rsoc
	#print("Battery 2 level %s" %battlevel_b2)
	battery_past_value_b2 = battery_present_value_b2
	battery_present_value_b2 = battlevel_b2
	delta_b2 = battery_present_value_b2 - battery_past_value_b2

	if (delta_b2 != battery_present_value_b2):
		if (delta_b2 > 0):
			print("Battery charging")
			yellow_warning_b2 = False
			red_warning_b2 = False
		elif (delta_b2 < 0):
			print("Battery discharging")
		
		if (battery_past_value_b2 > 97):
			print("Battery fully charged!")
	
	if (battlevel_b2 < battery_yellow_warning) and (yellow_warning_b2 == False):
		print("Yo be careful. Battery 2 will die in the future")
		# Yellow warning has been delayed
		yellow_warning_b2 = True

	if (battlevel_b2 < battery_red_warning) and (red_warning_b2 == False):
		print("Yo be even more careful. Battery 2 Dying")
		# Red warning has been displayed
		red_warning_b2 = True


rospy.init_node("alert_node")
print("Battery alert activated")
rospy.Subscriber("batt1level", JbdStatus, callback1)
rospy.Subscriber("batt2level", JbdStatus, callback2)


rospy.spin()