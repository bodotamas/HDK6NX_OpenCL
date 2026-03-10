// See https://aka.ms/new-console-template for more information
Console.WriteLine("Hello, World!");

Random random = new Random();

Console.WriteLine($"Random int = {random.Next()}");
Console.WriteLine($"Random in [0, 9] = {random.Next(11)}");
Console.WriteLine($"Random in [10, 20] = {random.Next(10, 21)}");
Console.WriteLine($"Random float in [0, 1) = {random.NextDouble()}");
