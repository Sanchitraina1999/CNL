import java.net.*;
import java.io.*;
public class server
{
    public static void main(String args[])throws IOException
    {
        byte b[]=new byte[3072];
        DatagramSocket dsoc=new DatagramSocket(1000);
        FileOutputStream f=new FileOutputStream("D:/nandha.txt");
        while(true)
        {
                    DatagramPacket dp=new DatagramPacket(b,b.length);
                    dsoc.receive(dp);
                    System.out.println(new String(dp.getData(),0,dp.getLength()));                             

        }
    }
}