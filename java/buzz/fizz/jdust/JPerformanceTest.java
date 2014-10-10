/**
 * Copyright (c) 2014 Tom Alexander; Released under the ISC License
 * https://github.com/craftkiller/jdust
 */
package buzz.fizz.jdust;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class JPerformanceTest
{
    private static String readFile(String path)
    {
        Path p = Paths.get(path);
        try 
        {
            byte[] rawData = Files.readAllBytes(p);
            return new String(rawData);
        } catch (IOException e) {
            System.out.println("Error loading " + path);
        }
        return "";
    }
    
    public static void main(String[] args)
    {
        String fullDust = readFile(args[0]);
        String dustTemplate = readFile(args[1]);
        JDust dust = new JDust();
        for (int i = 0; i < 1000; ++i)
        {
            dust.renderDust(fullDust, dustTemplate, "{'title': 'Hello Title'}");
        }
    }
}
