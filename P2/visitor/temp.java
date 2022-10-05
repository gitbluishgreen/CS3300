class temp1 extends temp1
{
	int x;
	String z;
	public temp1()
	{

	}
	public temp1 mango(double x)
	{
		help();
		//temp2 temp2 = new temp2();
		return new temp1();
	}
	// public temp1 mango(temp2 x)
	// {
	// 	help();
	// 	//temp2 temp2 = new temp2();
	// 	return new temp2();
	// }
	public void help()
	{
		String a = "hello";
		String b = a;
		while(b.length() != 1)
		{
			b = b.substring(0,b.length()-1);
		}
		System.out.println(a + " " + b);
	}
}

class temp2 extends temp1
{
	int x2;
	public temp2 mango(int x)
	{
		int temp1 = 28700;
		System.out.println("I got you!");
		return new temp2();
	}
}
class temp
{
	
	int m1;
	//float m1;
	public static void main(String arg[])
	{
		temp2 obj = new temp2();
		obj.mango(20.23);
		//obj.mango(2);

	}
}
