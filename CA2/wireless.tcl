if { $argc != 3 } {
	puts "Enter error rate, bandwidth, and pacet_size"
	abort()
}
set errorRate [lindex $argv 0]
set bandWidth [lindex $argv 1].Mb
set packetSize [lindex $argv 2].Kb
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

set throughput0 [open throughput0.tr w]
set throughput1 [open throughput1.tr w]

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

set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]

#balancer
set n4 [$ns node]	
#balancer

set n5 [$ns node]
set n6 [$ns node]
set n7 [$ns node]
set n8 [$ns node]

$n0 random-motion 0
$n1 random-motion 0
$n2 random-motion 0
$n3 random-motion 0
$n4 random-motion 0
$n5 random-motion 0

# Nodes size
$ns initial_node_pos $n0 20
$ns initial_node_pos $n1 20
$ns initial_node_pos $n2 20
$ns initial_node_pos $n3 20
$ns initial_node_pos $n4 20
$ns initial_node_pos $n5 20
$ns initial_node_pos $n6 20
$ns initial_node_pos $n7 20
$ns initial_node_pos $n8 20

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

$n7 set X_ 200.0
$n7 set Y_ 280.0
$n7 set Z_ 0.0

$n8 set X_ 200.0
$n8 set Y_ 180.0
$n8 set Z_ 0.0

set tcp0_4 [new Agent/TCP]
set tcp1_4 [new Agent/TCP]
set tcp2_4 [new Agent/TCP]
set tcp3_4 [new Agent/TCP]

set sink0_4 [new Agent/TCPSink]
set sink1_4 [new Agent/TCPSink]
set sink2_4 [new Agent/TCPSink]
set sink3_4 [new Agent/TCPSink]

$ns attach-agent $n0 $tcp0_4
$ns attach-agent $n1 $tcp1_4
$ns attach-agent $n2 $tcp2_4
$ns attach-agent $n3 $tcp3_4

$ns attach-agent $n4 $sink0_4
$ns attach-agent $n4 $sink1_4
$ns attach-agent $n4 $sink2_4
$ns attach-agent $n4 $sink3_4

$ns connect $tcp0_4 $sink0_4
$ns connect $tcp1_4 $sink1_4
$ns connect $tcp4_4 $sink2_4
$ns connect $tcp3_4 $sink3_4