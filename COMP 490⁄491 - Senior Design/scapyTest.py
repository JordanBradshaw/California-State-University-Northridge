import sched
import time
from collections import Counter

from scapy.all import ARP, sniff
from scapy.sendrecv import AsyncSniffer

## Create a Packet Counter
packet_counts = Counter()

timer = 0
## Define our Custom Action function
def custom_action(packet):
    # Create tuple of Src/Dst in sorted order
    key = tuple(sorted([packet.src, packet.dst]))
    packet_counts.update([key])
    global timer
    timer = 30
    # duration is in seconds
    return f"Packet #{sum(packet_counts.values())}: {packet.src} ==> {packet.dst}"

sniffer = AsyncSniffer(filter="ip and port 50007", prn=lambda x: x.show(), count=1, iface="lo")
sniffer = AsyncSniffer(filter="ip and port 50007", prn=custom_action, iface="lo")
sniffer.start()
while(1):
    audioList = []
    while(timer!=0):
        print(timer)

        time.sleep(1)
        timer -= 1
    #saveMic
    audioList.clear()
sniffer.join()
print(len(sniffer.results))

## Print out packet count per A <--> Z address pair
