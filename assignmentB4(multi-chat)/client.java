import java.util.*;
import java.net.*;
import java.io.*;

class client implements Runnable
{
		public static MulticastSocket socket;
		public static Boolean flag=false;
		public static InetAddress group=null;
		public static InetAddress local=null;
	public static void main(String[] args)
	{
		Scanner sc=new Scanner(System.in);
		
		BufferedReader br;
	
		try
		{
			socket=new MulticastSocket(8888);
			br=new BufferedReader(new InputStreamReader(System.in));
			group=InetAddress.getByName("230.0.0.1");
			local=InetAddress.getByName("localhost");
			socket.joinGroup(group);
			new Thread(new client()).start();

			while(true)
			{
				String s1=sc.next();
				byte rec1[]=new byte[100];
				rec1=s1.getBytes();
				DatagramPacket sendpacket=new DatagramPacket(rec1,rec1.length,local,9999);
				socket.send(sendpacket);
				flag=true;
			}
		}	
		catch(Exception e)
		{
			e.printStackTrace();
		}
	}
	@Override
	public  void run()
	{
		try
		{
			while(true)
			{
				byte rec1234[]=new byte[100];
				DatagramPacket receivepacket=new DatagramPacket(rec1234,rec1234.length,group,9999);
				socket.receive(receivepacket);
				String s12=new String(receivepacket.getData());
				if(!flag==true)
					System.out.println(s12);
				flag=false;
			}
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
	} 
}