class temp
{
	public static void main(String[] agr)
	{
		System.out.println(new A().solve());
	}
}
class A
{
	public int solve()
	{
		int y;
		
		B obj;
		obj = new B();
		y = 100;
		y = obj.hi(y);
		System.out.println(y);
		return 0;
	}
	public int hi(int z)
	{
		return 100;
	}
	public int jiggly()
	{
		return 0;
	}
}
class B extends A
{
public int hi(int z)
{
	return 200;
}
	public int solve()
	{
	return 0;
	}
	public int bruh()
	{
		return 0;
	}
}

class C extends B
{
	public int kundi()
{
	return 19;
}
}
class D extends C
{
public int jigglasasy()
{
	return 58;
}
}
