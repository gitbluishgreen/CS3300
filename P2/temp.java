class temp
{
	public static void main(String[] argu)
	{
		System.out.println(10);
	}
}
class temp2 extends temp1
{
	int x;
	int y;
	public float func(int y)
	{
		float z;
		return z;
	}
}
class temp1
{
	public int func(int y)
	{
		return 10;//overriding should not be allowed
	}
}
