using NUnit.Framework;
using System;

namespace Monotests.PrimerNS
{
    [TestFixture]
    public class PrimerTest : Assertion
    {
        [Test]
        public void SimpleCase()
        {
            Console.WriteLine("Tested!")
        }
    }
}
public class HelloWorld
{
    public static void Main(string[] args)
    {
        Console.WriteLine ("Hello, Mono!");
    }
}
