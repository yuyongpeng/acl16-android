package com.xkkj.hwspi;

public class StringHelper {
    public static String getNoBlankString(String str) {
        String text = "";

        text = str.replace(" ", "");
        text = text.replace("　", "");
        text = text.replace("\n", "");
        text = text.replace("\r", "");
        return text;
    }
}
