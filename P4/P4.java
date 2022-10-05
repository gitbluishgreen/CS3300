import syntaxtree.*;
import visitor.*;
import java.util.*;
public class P4
{
	public static void main(String[] arg)
	{
		try
		{
			Node root = new MiniIRParser(System.in).Goal();
			Integer x = new Integer(0);
			myDFS obj = new myDFS<String,Integer>();
       		root.accept(obj,x); // Your assignment part is invoked here.
			x = new Integer(1);
			root.accept(obj,x);
      	}
      	catch (ParseException e) {
         	System.out.println(e.toString());
      }
	}
}
