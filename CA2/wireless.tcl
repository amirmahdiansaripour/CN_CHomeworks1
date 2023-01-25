if { $argc != 3 } {
	puts "Enter error rate, bandwidth, and pacet_size"
	abort()
}
set error_rate [lindex $argv 0]
set packet_size [lindex $argv 1]Kb
set bandwidth [lindex $argv 2]Mb

# defining constants

set val(chan)           Channel/WirelessChannel    	;
set val(prop)           Propagation/TwoRayGround   	;
set val(netif)          Phy/WirelessPhy            	;
set val(mac)            Mac/802_11                 	;#MAC protocole
set val(ifq)            Queue/DropTail/PriQueue    	;
set val(ll)             LL                         	;
set val(ant)            Antenna/OmniAntenna        	;
set val(ifqlen)         50                         	;
set val(nn)             9                          	;
set val(rp)             AODV                       	;# routing protocol
set val(x)        		500							;
set val(y)        		500							;
set val(finish)         100                 		;
set ns [new Simulator]

set throughput4 [open throughput4.tr w]
set throughput5 [open throughput5.tr w]
set throughput6 [open throughput6.tr w]


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
set udp0_3 [new Agent/UDP]
set udp1_3 [new Agent/UDP]
set udp2_3 [new Agent/UDP]

set balancer0_3 [new Agent/Null]
set balancer1_3 [new Agent/Null]
set balancer2_3 [new Agent/Null]

$udp0_3 set packetSize_ $packet_size.Kb
$udp1_3 set packetSize_ $packet_size.Kb
$udp2_3 set packetSize_ $packet_size.Kb

$ns attach-agent $n0 $udp0_3
$ns attach-agent $n1 $udp1_3
$ns attach-agent $n2 $udp2_3
$ns attach-agent $n3 $balancer0_3
$ns attach-agent $n3 $balancer1_3
$ns attach-agent $n3 $balancer2_3

$ns connect $udp0_3 $balancer0_3
$ns connect $udp1_3 $balancer1_3
$ns connect $udp2_3 $balancer2_3

set cbr0_3 [new Application/Traffic/CBR]
set cbr1_3 [new Application/Traffic/CBR]
set cbr2_3 [new Application/Traffic/CBR]

$cbr0_3 attach-agent $udp0_3
$cbr1_3 attach-agent $udp1_3
$cbr2_3 attach-agent $udp2_3

## UDP part
set tcp3_4 [new Agent/TCP]
set tcp3_5 [new Agent/TCP]
set tcp3_6 [new Agent/TCP]
set sink3_4 [new Agent/TCPSink]
set sink3_5 [new Agent/TCPSink]
set sink3_6 [new Agent/TCPSink]

$tcp3_4 set packetSize_ $packet_size.Kb
$tcp3_5 set packetSize_ $packet_size.Kb
$tcp3_6 set packetSize_ $packet_size.Kb

$ns attach-agent $n3 $tcp3_4
$ns attach-agent $n3 $tcp3_5
$ns attach-agent $n3 $tcp3_6
$ns attach-agent $n4 $sink3_4
$ns attach-agent $n5 $sink3_5
$ns attach-agent $n6 $sink3_6

$ns connect $tcp3_4 $sink3_4
$ns connect $tcp3_5 $sink3_5
$ns connect $tcp3_6 $sink3_6

set cbr3_4 [new Application/Traffic/CBR]
set cbr3_5 [new Application/Traffic/CBR]
set cbr3_6 [new Application/Traffic/CBR]

$cbr3_4 attach-agent $tcp3_4
$cbr3_5 attach-agent $tcp3_5
$cbr3_6 attach-agent $tcp3_6


$ns at 0 "initNetwork"
$ns at 0 "$cbr0_3 start"
$ns at 0 "$cbr1_3 start"
$ns at 0 "$cbr2_3 start"
$ns at 0 "$cbr3_4 start"
$ns at 0 "$cbr3_5 start"
$ns at 0 "$cbr3_6 start"

set time 1


proc initNetwork {} {
    global sink3_4 sink3_5 sink3_6 ns time
    #Initialize sinks
    $sink3_4 set bytes_ 0
    $sink3_5 set bytes_ 0
    $sink3_6 set bytes_ 0
    
    set currTime [$ns now]
    $ns at [expr $currTime+$time] "handleSink"
}

proc handleSink {} {
    global sink3_4 sink3_5 sink3_6
    global throughput4 throughput5 throughput6 time ns

    set link3_4 [$sink3_4 set bytes_]
    set link3_5 [$sink3_5 set bytes_]
    set link3_6 [$sink3_6 set bytes_]
    
    set currTime [$ns now]
    # The load on sink
    set load4 [expr ($link3_4*8)/$time]
    set load5 [expr ($link3_5*8)/$time]
    set load6 [expr ($link3_6*8)/$time]

    puts $throughput4 "$currTime [expr $load4]"
    puts $throughput5 "$currTime [expr $load5]"
    puts $throughput6 "$currTime [expr $load6]"
    
    $sink3_4 set bytes_ 0
    $sink3_5 set bytes_ 0
    $sink3_6 set bytes_ 0
    # Repeat the process till time = 100
    $ns at [expr $currTime+$time] "handleSink"
}

proc finish {} {
    global ns tracefd namfile throughput4 throughput5 throughput6
    $ns flush-trace

    close $namfile
    close $tracefd

    close $throughput4
    close $throughput5
    close $throughput6
    
    exit 0
}

$ns at $val(finish) "finish"

$ns run
