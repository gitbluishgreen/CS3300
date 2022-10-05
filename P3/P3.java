import syntaxtree.*;
import visitor.*;
import java.util.*;
public class P3
{
	public static void main(String[] arg)
	{
		try
		{
			Node root = new MiniJavaParser(System.in).Goal();
			Integer x = new Integer(0);
			myDFS obj = new myDFS<Pair<Integer,String>,Integer>();
			boolean debug = obj.debug;
       		root.accept(obj,x); // Your assignment part is invoked here.
       		if(debug)
       		{
       			System.out.println("First pass okay!");
       			obj.debug();
       		}
			x = new Integer(1);
			root.accept(obj,x);
			//System.out.println("Program type checked successfully");
      	}
      	catch (ParseException e) {
         	System.out.println(e.toString());
      }
	}
}
