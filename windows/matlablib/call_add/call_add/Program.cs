using add;
using MathWorks.MATLAB.NET.Arrays;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace call_add
{
    class Program
    {
        static void Main(string[] args)
        {
            Class1 a = new Class1();
            MWArray b = 3, c = 6;
            MWArray result = a.add(b, c);
            Console.WriteLine(result.ToString());
            Console.Read();
        }
    }
}
