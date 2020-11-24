import java.util.*;
import java.net.*;
import java.io.*;

class peerclient
{
	public static void main(String[] args)
	{
		DatagramSocket socket;
		BufferedReader br;
		try
		{
			socket=new DatagramSocket();
			br=new BufferedReader(new InputStreamReader(System.in));
			InetAddress server=InetAddress.getByName("localhost");
			
			while(true)
			{
				System.out.println("Enter message");
				System.out.print(">");
				String s1=br.readLine();
				byte rec1[]=new byte[100];
				rec1=s1.getBytes();
				DatagramPacket sendpacket=new DatagramPacket(rec1,rec1.length,server,8888);
				socket.send(sendpacket);

				byte rec2[]=new byte[100];
				DatagramPacket receicepacket=new DatagramPacket(rec2,rec2.length);
				socket.receive(receicepacket);
				String s2=new String(receicepacket.getData());
				System.out.println(receicepacket.getAddress().getHostAddress()+"/"+receicepacket.getPort()+">"+s2);

			}
			
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
	}
}