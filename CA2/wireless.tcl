if { $argc != 3 } {
	puts "Enter error rate, bandwidth, and pacet_size"
	abort()
}
set error_rate [lindex $argv 0]
set bandwidth [lindex $argv 1].Mb
set packet_size [lindex $argv 2].Kb
# defining constants

set val(chan)           Channel/WirelessChannel    	;# Type of channel
set val(prop)           Propagation/TwoRayGround   	;# Radio model (propagation)
set val(netif)          Phy/WirelessPhy            	;# NIC (Interface Card)
set val(mac)            Mac/802_11                 	;# Medium Access Control (MAC)
set val(ifq)            Queue/DropTail/PriQueue    	;# Type of queuing interface
set val(ll)             LL                         	;# link layer type
set val(ant)            Antenna/OmniAntenna        	;# Antenna Model
set val(ifqlen)         50                         	;# max packet in interface queue
set val(nn)             9                          	;# number of mobilenodes
set val(rp)             AODV                       	;# routing protocol
set val(x)        		500							;# in meters
set val(y)        		500							;# in meters
set val(finish)         100.0               		;# finish time
set ns [new Simulator]

set throughput5 [open throughput5.tr w]
# set throughput6 [open throughput6.tr w]
# set throughput7 [open throughput7.tr w]
# set throughput8 [open throughput8.tr w]


$ns use-newtrace
set name wireless
set tracefd [open $name.tr w]
set namfile [open $name.nam w]
$ns trace-all $tracefd
$ns namtrace-all-wireless $namfile $val(x) $val(y)


Mac/802_11 set dataRate_ $bandwidth.Mb
Mac/802_11 set RTSThreshold_    1

#Network topography
set topo [new Topography]
$topo load_flatgrid $val(x) $val(y)
create-god $val(nn)
set channel1 [new $val(chan)]

proc HandleErrorRate {} {
    global  error_rate
    set errorModel [new ErrorModel]
    $errorModel unit packet;
    $errorModel set rate_ $error_rate
    return $errorModel
}

# defining node
$ns node-config -adhocRouting $val(rp) \
			 	-llType $val(ll) \
			 	-macType $val(mac) \
			 	-ifqType $val(ifq) \
			 	-ifqLen $val(ifqlen) \
			 	-antType $val(ant) \
			 	-propType $val(prop) \
			 	-phyType $val(netif) \
			 	-topoInstance $topo \
			 	-agentTrace ON \
			 	-macTrace ON \
			 	-routerTrace ON \
			 	-movementTrace ON \
			 	-channel $channel1

#set nodes
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
#balancer
set n3 [$ns node]	
#balancer
set n4 [$ns node]
set n5 [$ns node]
set n6 [$ns node]

# Nodes random motion
$n0 random-motion 0
$n1 random-motion 0
$n2 random-motion 0
$n3 random-motion 0
$n4 random-motion 0
$n5 random-motion 0
$n6 random-motion 0

# Nodes size
$ns initial_node_pos $n0 20
$ns initial_node_pos $n1 20
$ns initial_node_pos $n2 20
$ns initial_node_pos $n3 20
$ns initial_node_pos $n4 20
$ns initial_node_pos $n5 20
$ns initial_node_pos $n6 20

#Nodes locations
$n0 set X_ 50.0
$n0 set Y_ 330.0
$n0 set Z_ 0.0
$n1 set X_ 0.0
$n1 set Y_ 230.0
$n1 set Z_ 0.0
$n2 set X_ 50.0
$n2 set Y_ 130.0
$n2 set Z_ 0.0
$n3 set X_ 100.0
$n3 set Y_ 180.0
$n3 set Z_ 0.0
$n4 set X_ 100.0
$n4 set Y_ 280.0
$n4 set Z_ 0.0
$n5 set X_ 150.0
$n5 set Y_ 280.0
$n5 set Z_ 0.0
$n6 set X_ 150.0
$n6 set Y_ 180.0
$n6 set Z_ 0.0

#TCP connections
set tcp0_3 [new Agent/TCP]
set tcp1_3 [new Agent/TCP]
set tcp2_3 [new Agent/TCP]
set tcp3_3 [new Agent/TCP]

set sink0_3 [new Agent/TCPSink]
set sink1_3 [new Agent/TCPSink]
set sink2_3 [new Agent/TCPSink]

$tcp0_3 set packetSize_ $packet_size.Kb
$tcp1_3 set packetSize_ $packet_size.Kb
$tcp2_3 set packetSize_ $packet_size.Kb

$ns attach-agent $n0 $tcp0_3
$ns attach-agent $n1 $tcp1_3
$ns attach-agent $n2 $tcp2_3

$ns attach-agent $n3 $sink0_3
$ns attach-agent $n3 $sink1_3
$ns attach-agent $n3 $sink2_3

$ns connect $tcp0_3 $sink0_3
$ns connect $tcp1_3 $sink1_3
$ns connect $tcp2_3 $sink2_3

set cbr0_3 [new Application/Traffic/CBR]
set cbr1_3 [new Application/Traffic/CBR]
set cbr2_3 [new Application/Traffic/CBR]
set cbr3_3 [new Application/Traffic/CBR]

$cbr0_3 attach-agent $tcp0_3
$cbr1_3 attach-agent $tcp1_3
$cbr2_3 attach-agent $tcp2_3

$ns at 0.0 "initNetwork"
$ns at 0.0 "$cbr0_3 start"
$ns at 0.0 "$cbr1_3 start"
$ns at 0.0 "$cbr2_3 start"

set time 1.0

proc initNetwork {} {
    global sink0_3 sink1_3 sink2_3 ns time
    #Initialize sinks
    $sink0_3 set bytes_ 0
    $sink1_3 set bytes_ 0
    $sink2_3 set bytes_ 0
    
    set currTime [$ns now]
    $ns at [expr $currTime+$time] "handleSink"
}

proc handleSink {} {
    global sink0_3 sink1_3 sink2_3
    global throughput5 time ns packet_size
    # global throughput5 throughput6 throughput7 throughput8 time ns packet_size

    set link0_3 [$sink0_3 set bytes_]
    set link1_3 [$sink1_3 set bytes_]
    set link2_3 [$sink2_3 set bytes_]
    
    set currTime [$ns now]
    # The load on sink
    set load3 [expr ($link0_3*8)/$time + ($link1_3*8)/$time + ($link2_3*8)/$time]

    puts $throughput5 "$currTime [expr $load3]"
    $sink0_3 set bytes_ 0
    $sink1_3 set bytes_ 0
    $sink2_3 set bytes_ 0
    # Repeat the process till time = 100
    $ns at [expr $currTime+$time] "handleSink"
}

proc finish {} {
    global ns tracefd namfile throughput5
    $ns flush-trace

    close $namfile
    close $tracefd

    close $throughput5
    exit 0
}

$ns at $val(finish) "finish"

$ns run
