public class HelloRunnable extends Thread
{

	public void run() {
		System.out.println("Hello from a thread!");
	}

	public static void main(String args[])
	{
		(new Thread(new HelloRunnable())).start();
	}
}
