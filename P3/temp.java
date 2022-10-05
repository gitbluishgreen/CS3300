class temp
{
	public static void main(String[] arg)
	{
		apple a;
		mango b = new mango();
		a = b;
		System.out.println(a.foo1(10,20));
	}
}
class mango extends apple
{
	public int x;
	public int foo1(int y,int z)
	{
		return (10 + y) + z;
	}
}
class apple
{
	public int x = -10;
	public int foo1(int y,int z)
	{
		x = 30;
		return y+z+100;
	}
}
class obj extends mango
{
	public int foo()
	{
		return 10;
	}	
}