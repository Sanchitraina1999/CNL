import java.util.*;
import java.net.*;
import java.io.*;

class server
{
	public static void main(String[] args)
	{
		DatagramSocket socket;
		BufferedReader br;
		try
		{
			socket=new DatagramSocket(9999);
			br=new BufferedReader(new InputStreamReader(System.in));
			InetAddress group=InetAddress.getByName("230.0.0.1");
			

			while(true)
			{	
				byte rec1[]=new byte[100];
				DatagramPacket receivepacket=new DatagramPacket(rec1,rec1.length);
				socket.receive(receivepacket);
				String s1=new String(receivepacket.getData());
				System.out.println(s1);

				byte rec2[]=new byte[100];
				rec2=s1.getBytes();
				DatagramPacket sendpacket=new DatagramPacket(rec2,rec2.length,group,8888);
				socket.send(sendpacket);
			}
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}	
	}
}