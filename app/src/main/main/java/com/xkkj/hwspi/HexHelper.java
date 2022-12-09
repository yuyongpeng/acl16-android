package com.xkkj.hwspi;

public class HexHelper {
    /** 16进制中的字符集 */
    private static final String HEX_CHAR = "0123456789ABCDEF";
    /**
     * 16进制表示的字符串转换为字节数组
     *
     * @param s 16进制表示的字符串
     * @return byte[] 字节数组
     */
    public static byte[] hexStringToByteArray(String s) {
        int len = s.length();
        byte[] b = new byte[len / 2];
        for (int i = 0; i < len; i += 2) {
            // 两位一组，表示一个字节,把这样表示的16进制字符串，还原成一个字节
            b[i / 2] = (byte) ((Character.digit(s.charAt(i), 16) << 4) + Character
                    .digit(s.charAt(i + 1), 16));
        }
        return b;
    }


    public static String bytes2HexStrBlank(byte[] b) {
        String r = "";

        for (int i = 0; i < b.length; i++) {
            String hex = Integer.toHexString(b[i] & 0xFF);
            if (hex.length() == 1) {
                hex = '0' + hex;
            }
            r += hex.toUpperCase() + " ";
        }

        return r;
    }

    public static String bytes2HexStr(byte[] b) {
        String r = "";

        for (int i = 0; i < b.length; i++) {
            String hex = Integer.toHexString(b[i] & 0xFF);
            if (hex.length() == 1) {
                hex = '0' + hex;
            }
            r += hex.toUpperCase();
        }

        return r;
    }



    /**
     * 16进制字节数组转换为10进制字节数组
     *
     * 两个16进制字节对应一个10进制字节，则将第一个16进制字节对应成16进制字符表中的位置(0~15)并向左移动4位，
     * 再与第二个16进制字节对应成16进制字符表中的位置(0~15)进行或运算，则得到对应的10进制字节
     * @param b 10进制字节数组
     * @return 16进制字节数组
     */
    public static byte[] hex2byte(byte[] b) {
        if(b.length%2 != 0) {
            throw new IllegalArgumentException("byte array length is not even!");
        }

        int length = b.length >> 1;
        byte[] b2 = new byte[length];
        int pos;
        for(int i=0; i<length; i++) {
            pos = i << 1;
            b2[i] = (byte) (HEX_CHAR.indexOf( b[pos] ) << 4 | HEX_CHAR.indexOf( b[pos+1] ) );
        }
        return b2;
    }

    /**
     * 将16进制字节数组转成10进制字符串
     * @param b 16进制字节数组
     * @return 10进制字符串
     */
    public static String hex2Str(byte[] b) {
        return new String(hex2byte(b));
    }
}
