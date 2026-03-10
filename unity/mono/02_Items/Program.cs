using Classes;
using System;
using System.Collections.Generic;

/// <summary>
/// A sample application
/// </summary>
public class App
{
    /// <summary>
    /// Count the valid items in the list of items.
    /// </summary>
    /// <param name="items">List of items</param>
    /// <returns>Count of valid items</returns>
    public static int CountValidItems(List<Item> items)
    {
        int count = 0;
        foreach (var item in items)
        {
            if (item.IsValid)
            {
                count++;
            }
        }
        return count;
    }

    /// <summary>
    /// Entry point of the program.
    /// </summary>
    public static void Main(string[] args)
    {
        List<Item> items = new List<Item>();
        for (int i = 0; i < 20; i++)
        {
            Item item;
            if (i % 3 == 0)
            {
                item = new Item(true);
            }
            else
            {
                item = new Item(false);
            }
            items.Add(item);
        }
        int nValidItems = CountValidItems(items);
        Console.WriteLine($"Count of items: {items.Count}");
        Console.WriteLine($"Count of valid items: {nValidItems}");
    }
}

