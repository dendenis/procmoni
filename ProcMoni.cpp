using System;
using System.Management;

class Process {
  public static void Main() {
    ManagementEventWatcher startWatch = new ManagementEventWatcher(
      new WqlEventQuery("SELECT * FROM Win32_ProcessStartTrace"));
    startWatch.EventArrived += new EventArrivedEventHandler(startWatch_EventArrived);
    startWatch.Start();
    ManagementEventWatcher stopWatch = new ManagementEventWatcher(
      new WqlEventQuery("SELECT * FROM Win32_ProcessStopTrace"));
    stopWatch.EventArrived += new EventArrivedEventHandler(stopWatch_EventArrived);
    stopWatch.Start();
    Console.WriteLine("Press any key to exit");
    while (!Console.KeyAvailable) System.Threading.Thread.Sleep(50);
    startWatch.Stop();
    stopWatch.Stop();
  }

  static void stopWatch_EventArrived(object sender, EventArrivedEventArgs e) {
    Console.WriteLine("Process stopped: {0}", e.NewEvent.Properties["ProcessName"].Value);
  }

  static void startWatch_EventArrived(object sender, EventArrivedEventArgs e) {
    Console.WriteLine("Process started: {0}", e.NewEvent.Properties["ProcessName"].Value);
  }
}
