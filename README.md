# EQUAL-COST-MULTIPATH-ROUTING
Equal-cost multipath (ECMP) is a network routing strategy that allows for traffic of the same session, or flow—that is, traffic with the same source and destination—to be transmitted across multiple paths of equal cost. It is a mechanism that allows you to load balance traffic and increase bandwidth by fully utilizing otherwise unused bandwidth on links to the same destination.

# IMPLEMENTING ECMP
Basic ECMP can be implemented using Balanced Round robin algorithm.The Balanced Round Robin algorithm distributes incoming sessions equally across the links, favoring load balancing over session stickiness. (Round robin indicates a sequence in which the least recently chosen item is chosen.) In addition, if new routes are added or removed from an ECMP group (for example if a path in the group goes down), the virtual router will re-balance the sessions across links in the group. Additionally, if the flows in a session have to switch routes due to an outage, when the original route associated with the session becomes available again, the flows in the session will revert to the original route when the virtual router once again re-balances the load.

![image](https://user-images.githubusercontent.com/90191497/150070661-ab1fe242-dfba-4f86-8fbb-e5b43c923213.png)
