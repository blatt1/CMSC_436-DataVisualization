import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class GenPbm {
/*	0 to 4
	5 to 14
	15 to 17
	18 to 24
	25 to 34
	35 to 44
	45 to 64
	65 and over */
	static int age_0to4 = 0;
	static int age_5to14 = 0;
	static int age_15to17 = 0;
	static int age_18to24 = 0;
	static int age_25to34 = 0;
	static int age_35to44 = 0;
	static int age_45to64 = 0;
	static int age_65andOver = 0;

	public static void main(String[] args) 
	{
		//System.out.println("Hello!!!");
		BufferedReader br = null;
		try
		{
			String sCurrentLine;
			// br = new BufferedReader(new FileReader("/home/boeing/Downloads/data1.txt"));
			br = new BufferedReader(new FileReader("/home/boeing/Downloads/data2ehrSample.csv"));
			//System.out.println("{\"points\":[");
			int lineCount = 0;
			while ((sCurrentLine = br.readLine()) != null)
			{
				//System.out.println(sCurrentLine);
				gen(sCurrentLine, lineCount);
				lineCount++;
			}
			//System.out.print('\b');
			//System.out.println("]}");
			System.out.println("0 to 4 : " + age_0to4);
			System.out.println("5 to 14 : " + age_5to14);
			System.out.println("15 to 17 : " + age_15to17);
			System.out.println("18 to 24 : " + age_18to24);
			System.out.println("25 to 34 : " + age_25to34);
			System.out.println("35 to 44 : " + age_35to44);
			System.out.println("45 to 64 : " + age_45to64);
			System.out.println("65 and over : " + age_65andOver);
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}
		finally
		{
			try
			{
				if (br != null)br.close();
			}
			catch (IOException ex)
			{
				ex.printStackTrace();
			}
		}
	}
	
	public static void genPbm(String in, int lineNum)
	{
		String[] toks = in.split(" ");
		//System.out.println("String array's length : " + toks.length);
		for (int i = 0; i < toks.length; i++)
		{
			System.out.println("{\"x\":\"" + i + "\", \"y\":\"" + lineNum + "\", \"val\":\"" + toks[i] + "\"},");
			/*
			float num = Float.parseFloat(toks[i]); 
			if (num == 0.0f)
			{
			    System.out.print("0"); System.out.print(" ");
			}
			else
			{
				System.out.print("1"); System.out.print(" ");
			}
			*/
		}
		//System.out.print("\n");
	}
	
	public static void gen(String in, int lineNum)
	{
		//System.out.println(in);
		String[] toks = in.split("\t");
		
		int idx = 33;
		if (lineNum == 0)
		{
			System.out.println(toks[3] + ", " + toks[idx]);
		}
		
		if ((toks[3].equals("0 to 4")) && (toks[idx].equals("1")))
		{
			age_0to4++;
		}
		else if((toks[3].equals("5 to 14")) && (toks[idx].equals("1")))
		{
			age_5to14++;
		}
		else if((toks[3].equals("15 to 17")) && (toks[idx].equals("1")))
		{
			age_15to17++;
		}
		else if((toks[3].equals("18 to 24")) && (toks[idx].equals("1")))
		{
			age_18to24++;
		}
		else if((toks[3].equals("25 to 34")) && (toks[idx].equals("1")))
		{
			age_25to34++;
		}
		else if((toks[3].equals("35 to 44")) && (toks[idx].equals("1")))
		{
			age_35to44++;
		}
		else if((toks[3].equals("45 to 64")) && (toks[idx].equals("1")))
		{
			age_45to64++;
		}
		else if((toks[3].equals("65 and over")) && (toks[idx].equals("1")))
		{
			age_65andOver++;
		}
		/*
		String[] toks = in.split(" ");
		//System.out.println("String array's length : " + toks.length);
		for (int i = 0; i < toks.length; i++)
		{
			System.out.println("{\"x\":\"" + i + "\", \"y\":\"" + lineNum + "\", \"val\":\"" + toks[i] + "\"},");
			/*
			float num = Float.parseFloat(toks[i]); 
			if (num == 0.0f)
			{
			    System.out.print("0"); System.out.print(" ");
			}
			else
			{
				System.out.print("1"); System.out.print(" ");
			}
			*/
		//}
		//System.out.print("\n");
	}
}
