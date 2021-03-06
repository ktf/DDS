# DDS Release Notes

## v0.10 (NOT YET RELEASED)
### DDS common
Added: handlers of the monitoring thread can be registered now with custom call intervals. (GH-63)   
Added: accumulated push message function. (GH-64)   
Added: include std c++ lib into worker package. (GH-61)   
Added: nicer logging on monitoring thread actions. (GH-80)     
Added: additional log levels. DDS has learned 3 new levels of protocol log events. (GH-49)    
Fixed: fix implementation of cmdSHUTDOWN. (GH-65)   
Fixed: remove shared memory on exit.    
Fixed: fix monitoring thread to prevent breaks if custom callbacks throw exceptions. (GH-80)  
Modified: Name of task output file changed to "user_task_<datetime>_<task_id>_<out/err>.log". (GH-75)    

### dds scout
Modified: New lock algorithm, instead of the lockfile command.    

### dds-commander
Added: Since dds-commander is a daemon and doesn't have a console, it now has a dedicated log file for its std-out/-err called "dds-commander.out.log". File is located in the log directory.   

### dds-topology
Added: output time spent on activation. (GH-62)    
Added: the command learned "--set" parameter, which is used to set up topology for the current deployment. (GH-56)   
Added: the command learned "--disiable-validation", which is used to disable topology validation. It can be used only together with "--set". (GH-56)   
Added: scheduling and requirements for the collections. (GH-76)    
Added: index for tasks and collections which are in groups. (GH-72)   
Added: new test for task and collection indices. (GH-72)   
Added: variable definition in the topology. (GH-71)

### dds-submit
Modified: removed "--topo" parameter. (GH-56)   
Modified: removed "--disable-xml-validation" parameter. (GH-56)   

### dds-agent
Fixed: reconnect to DDS commander if connection was dropped. (GH-77)   
Fixed: after reconnection to commander server key update won't be propagate from the effected agent. (GH-81)    
Modified: Optimized key-value persistence to shared memory.   

### dds-key-value
Fixed: stability improvements.    
Added: Multiple subscribers for key-value notifications. (GH-70)   
Added: If task can only read property then property will not be propagated. (GH-55)   
Added: User task can subscribe to error events, for example, error will be send if property can not be propagated. (GH-55)   

### dds-user-defaults
Modified: use string log severity values instead of numbers. (GH-49)    

## v0.8 (2015-02-17)
### DDS common
Fixed: idle time calculation for dds-commander and dds-agent. (GH-32)   
Fixed: a bug, which prevented log files to rotate.    
Fixed: reaching the idle timeout causes Commander and Agents to exit even if user processes are still running. (GH-54)    
Added: Log rotation: maximum total size of the stored log files is 1GB. (GH-36)    
Added: Log rotation: minimum free space on the drive after which older log files will be deleted is 2GB. (GH-36)    
Added: User's task stdout/err on WNs are automatically written in dedicated log files, user_task_<TASK_ID>_out.log and user_task_<TASK_ID>_err.log accordingly. (GH-26)   
Added: Progress display for "dds-agent-cmd getlog", "dds-topology --activate" and "dds-test -t" in percent. Optionally full verbose messages can be displayed with --verbose option. (GH-42)   
Added: Broadcast property deletion on task exit. (GH-28)   
Added: property propagation types. (GH-30)   

### dds-commander
Added: State of agents. (GH-27)    

### dds-user-defaults
Modified: Default log level is changed to 1 (instead of 0).   
Modified: Log rotation: default log rotations size in MB instead of bytes. (default is 10 MB).   

### dds-ssh
Added: the ssh plug-in has been extended to support multiple agents per host. (GH-25)   
Added: each DDS scout uses separate stderr/-out file (scout.log), when more than one worker requested per machine.   

### dds-key-value
Added: users are now able to subscribe on properties update events. (GH-29)   
Added: shared memory storage for key-value. (GH-35)   

### dds-protocol-lib
Modified: The DDS transport learned to accumulate commands before sending, instead of sending them one by one. (GH-38)   
Modified: Hand-shake messages are prioritized now. DDS doesn't send/accept any other message until hand-shake is successful. (GH-37)   
Fixed: Revised write message algorithms. It is also faster now.    
Fixed: a bug in the dds-agent, which could cause a SEGFAULT when trying to access a deleted channel object on disconnect.    
Added: Implemented callbacks (signals) in BaseChannelImpl for different channel events like connect, disconnect, handshakeOK, handshakeFailed. (GH-41)   
Fixed: Stability improvements. Handling edge cases which could occur during channel destruction. 

### dds-info
Added: taskId and task name to console output (dds-info -l). (GH-33)    
Added: possibility to get property list and property values from agents. (GH-52)

### dds-topology
Added: Users are now able to stop (restart) execution of tasks by calling "dds-topology --stop". To restart call: "dds-topology --stop" and "dds-topology --activate". (GH-31)    
Fixed: a bug, which caused a crash when topology activate is called before dds-submit. (GH-51)   

## v0.6 (2014-12-05)
### DDS common   
Modified: Build WN packages without ICU support. (GH-14)   
Added: key-value propagation support. (GH-12)   
Added: key-value propagation API lib. (GH-11)   
Fixed: Arguments of the task executable could contain slashes.   
Added: Simple scheduler for SSH which takes into account requirements. (GH-20)   
Added: Startup time of agents. It can be requested via git-info -l. (GH-3)   

### dds-protocol-lib
Modified: Version changed to v2.0.   
Added: The protocol has learned a new command - cmdUPDATE_KEY. (GH-12)   
Added: BinaryAttachment command learned to resolve environment variables in source files paths.

### dds-topology
Added: a possibility to use comments in the topology XML file. (GH-15)   
Renamed: dds-topology renamed to dds-topology-lib. dds-topology is executable now.   
Added: task activation functionality is moved from dds-submit to dds-topology.(GH-16)   

###dds-agent-cmd
Added: new command for communication with agents.(GH-17)   
Added: getlog functionality moved to dds-agent-cmd.(GH-17)   
Added: dds-agent-cmd learned a new command - update-key. It forces an update of a given task's property in the topology. (GH-12)   

## v0.4 (2014-10-24)
### DDS common
Added: DDS learned how to expand given user tasks commands with arguments given as a single string. (in the Topology->Task->exec parameter).   
Added: if a user's task is defined in the topology as not reachable, then DDS will take care of delivering it to worker nodes. (GH-6)   
Improved: all DDS CLI commands use now common code to find suitable DDS commander server.   
Modified: Updated User's manual.   
Modified: Improved stability.  

### dds-topology
Fixed: respond with an error if the given topo file is missing.   
Modified: the topology description schema has been revised. See User's manual for more details.   
Added: topology learned a new users' task attribute - "reachable". It defines whether executable is available on worker nodes. (GH-6)

### dds-submit
Modified: Stop server communication channel if a fatal error is received from the server.   
Added: Properly reflect server messages to stdout when agents are submitted/activated.   
Added: Show more informative messages in case if the ssh plug-in failed to deploy agents.   
Added: The command remembers now all options of the last successful call.   
Added: The command learned a new command line option "--config". It gives the possibility to specify a configuration file with predefined dds-submit options.   

### dds-protocol-lib
Improved: The protocol message header size has been reduced from 12 to 8 bytes.   
Improved: The protocol message header is validated now using CRC.   
Improved: Split binary files uploads into multiple message chunks, instead of using one message per file.

## v0.2 (2014-09-03)

The first stable internal release.

