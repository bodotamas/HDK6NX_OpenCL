using Classes;

/**
 * Count the valid items.
 */
static int CountValidItems(List<Item> items)
{
    int count = 0;
    foreach (Item item in items) {
        if (item.IsValid) {
            count++;
        }
    }
    return count;
}

// var item = new Item(false);
List<Item> items = new List<Item> {
    new Item(false),
    new Item(true),
    new Item(true)
};

Console.WriteLine("Hello, World!");
Console.WriteLine($"Number of valid items: {CountValidItems(items)}");
