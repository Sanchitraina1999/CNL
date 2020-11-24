import java.util.*;
import java.net.*;
import java.io.*;

class peerserver
{
	public static void main(String[] args)
	{
		DatagramSocket socket;
		BufferedReader br;
		try
		{
			socket=new DatagramSocket(8888);
			br=new BufferedReader(new InputStreamReader(System.in));

			while(true)
			{
				byte rec1[]=new byte[100];
				DatagramPacket receivepacket=new DatagramPacket(rec1,rec1.length);
				socket.receive(receivepacket);
				String s1=new String(receivepacket.getData());
				System.out.println(receivepacket.getAddress().getHostAddress()+"/"+receivepacket.getPort()+">"+s1);

				System.out.print(">");
				String s2=br.readLine();
				byte rec2[]=new byte[100];
				rec2=s2.getBytes();
				DatagramPacket sendpacket=new DatagramPacket(rec2,rec2.length,receivepacket.getAddress(),receivepacket.getPort());
				socket.send(sendpacket);
			}

		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
	}
}