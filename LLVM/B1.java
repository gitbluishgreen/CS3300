import syntaxtree.*;
import visitor.*;
public class B1
{
	public static void main(String[] arg)
	{
		try
		{
			Node root = new MiniJavaParser(System.in).Goal();
			Integer x = 0;
			GJVoidDepthFirst<Integer> obj = new GJVoidDepthFirst<Integer>();
			root.accept(obj,x);
			x++;   
			root.accept(obj,x);
      	}
      	catch (ParseException e) {
         	System.out.println(e.toString());
      }
	}
}