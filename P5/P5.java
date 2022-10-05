import syntaxtree.*;
import visitor.*;
import java.util.*;
public class P5
{
	public static void main(String[] arg)
	{
		try
		{
			Node root = new microIRParser(System.in).Goal();
			Integer x = new Integer(0);
			myDFS obj = new myDFS<String,Integer>();
       		root.accept(obj,x); // Your assignment part is invoked here.
			x++;
			//obj.print_nodes();//prints all the nodes in the program.
			//obj.print_live_ranges();//prints all the live ranges in the program.
			root.accept(obj,x);//first pass for function building
			x++;
			root.accept(obj,x);//code generation pass
      	}
      	catch (ParseException e) {
         	System.out.println(e.toString());
      }
	}
}
