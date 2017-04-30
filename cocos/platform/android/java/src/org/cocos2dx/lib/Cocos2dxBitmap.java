/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2014 Chukong Technologies Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
 ****************************************************************************/
package org.cocos2dx.lib;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.util.LinkedList;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Paint.Align;
import android.graphics.Paint.FontMetricsInt;
import android.graphics.Rect;
import android.graphics.Typeface;
import android.text.BoringLayout;
import android.text.Layout;
import android.text.StaticLayout;
import android.text.TextPaint;
import android.text.TextUtils;
import android.util.Log;

public final class Cocos2dxBitmap {
    // ===========================================================
    // Constants
    // ===========================================================

    /* The values are the same as cocos2dx/platform/CCImage.h. */
    private static final int HORIZONTAL_ALIGN_LEFT = 1;
    private static final int HORIZONTAL_ALIGN_RIGHT = 2;
    private static final int HORIZONTAL_ALIGN_CENTER = 3;
    private static final int VERTICAL_ALIGN_TOP = 1;
    private static final int VERTICAL_ALIGN_BOTTOM = 2;
    private static final int VERTICAL_ALIGN_CENTER = 3;

    // ===========================================================
    // Fields
    // ===========================================================

    private static Context sContext;

    // ===========================================================
    // Constructors
    // ===========================================================

    // ===========================================================
    // Getter & Setter
    // ===========================================================

    public static void setContext(final Context context) {
        Cocos2dxBitmap.sContext = context;
    }

    // ===========================================================
    // Methods for/from SuperClass/Interfaces
    // ===========================================================

    // ===========================================================
    // Methods
    // ===========================================================

    private static native void nativeInitBitmapDC(final int width,
            final int height, final byte[] pixels);

    /**
     * @param width
     *            the width to draw, it can be 0
     * @param height
     *            the height to draw, it can be 0
     */
 //   public static void createTextBitmap(String string, final String fontName,
 //           final int fontSize, final int alignment, final int width,
 //           final int height) {
        
 //       createTextBitmapShadowStroke( string.getBytes(), fontName, fontSize, 255,255, 255,255 ,    // text font and color
 //                                     alignment, width, height,                         // alignment and size
 //                                     false, 0.0f, 0.0f, 0.0f, 0.0f,                    // no shadow
 //                                     false, 255, 255, 255, 255, 12.0f,      // no stroke
//									  false, 0);                  
   //                                  
//    }

 public static int getTextHeight(String text, int maxWidth, float textSize, Typeface typeface) {
        TextPaint paint = new TextPaint(Paint.ANTI_ALIAS_FLAG | Paint.SUBPIXEL_TEXT_FLAG);
        paint.setTextSize(textSize);
        paint.setTypeface(typeface);

        int lineCount = 0;

        int index = 0;
        int length = text.length();

        while(index < length) {
            index += paint.breakText(text, index, length, true, maxWidth, null);
            lineCount++;
        }

        float actualHeight = (Math.abs(paint.ascent()) + Math.abs(paint.descent()));
        return (int)Math.floor(lineCount * actualHeight);
    }
	
	
	 public static Typeface calculateShrinkTypeFace(String text, int width, int height, Layout.Alignment hAlignment, float textSize, TextPaint paint, boolean enableWrap)
    {
        if (width == 0 || height == 0) {
            return  paint.getTypeface();
        }
        float actualWidth = width + 1;
        float actualHeight = height + 1;
        float fontSize = textSize + 1;

        if (!enableWrap) {
            while (actualWidth > width || actualHeight > height) {
                fontSize = fontSize - 1;

                actualWidth = (int)Math.ceil( StaticLayout.getDesiredWidth(text, paint));
                actualHeight = getTextHeight(text, (int)actualWidth, fontSize, paint.getTypeface());

                paint.setTextSize(fontSize);
                if (fontSize <= 0) {
                    paint.setTextSize(textSize);
                    break;
                }
            }
        } else {
            while (actualHeight > height || actualWidth > width) {
                fontSize = fontSize - 1;

                Layout layout = new StaticLayout(text, paint, (int) width, hAlignment,1.0f,0.0f,false);
                actualWidth = layout.getWidth();
                actualHeight = layout.getLineTop(layout.getLineCount());

                paint.setTextSize(fontSize);

                if (fontSize <= 0) {
                    paint.setTextSize(textSize);
                    break;
                }
            }

        }
        return paint.getTypeface();
    }

    public static boolean createTextBitmapShadowStroke(byte[] bytes,  final String fontName, int fontSize,
                                                       int fontTintR, int fontTintG, int fontTintB, int fontTintA,
                                                       int alignment, int width, int height,
                                                       boolean shadow, float shadowDX, float shadowDY, float shadowBlur, float shadowOpacity,
                                                       boolean stroke, int strokeR, int strokeG, int strokeB, int strokeA, float strokeSize, boolean enableWrap, int overflow) {
     String string;
        if (bytes == null || bytes.length == 0) {
          return false;
        } else {
          string = new String(bytes);
        }

        Layout.Alignment hAlignment = Layout.Alignment.ALIGN_NORMAL;
        int horizontalAlignment = alignment & 0x0F;
        switch (horizontalAlignment) {
            case HORIZONTAL_ALIGN_CENTER:
                hAlignment = Layout.Alignment.ALIGN_CENTER;
                break;
            case HORIZONTAL_ALIGN_RIGHT:
                hAlignment = Layout.Alignment.ALIGN_OPPOSITE;
                break;
            case HORIZONTAL_ALIGN_LEFT:
                break;
            default:
                break;
        }

        TextPaint paint = Cocos2dxBitmap.newPaint(fontName, fontSize);

        if (stroke) {
            paint.setStyle(TextPaint.Style.STROKE);
            paint.setStrokeWidth(strokeSize);
        }

        int maxWidth = width;

        if (maxWidth <= 0) {
            maxWidth = (int)Math.ceil( StaticLayout.getDesiredWidth(string, paint));
        }

        Layout layout = null;
        int layoutWidth = 0;
        int layoutHeight = 0;


        if (overflow == 1 && !enableWrap){
            int widthBoundary = (int)Math.ceil( StaticLayout.getDesiredWidth(string, paint));
            layout = new StaticLayout(string, paint, widthBoundary , hAlignment,1.0f,0.0f,false);
        }else {
            if (overflow == 2) {
                calculateShrinkTypeFace(string, width, height, hAlignment, fontSize, paint, enableWrap);
            }
            layout = new StaticLayout(string, paint, maxWidth , hAlignment,1.0f,0.0f,false);
        }

        layoutWidth = layout.getWidth();
        layoutHeight = layout.getLineTop(layout.getLineCount());

        int bitmapWidth = Math.max(layoutWidth, width);
        int bitmapHeight = layoutHeight;
        if (height > 0) {
            bitmapHeight = height;
        }

        if (overflow == 1 && !enableWrap) {
            if (width > 0) {
                bitmapWidth = width;
            }
        }

        if (bitmapWidth == 0 || bitmapHeight == 0) {
            return false;
        }

        int offsetX = 0;
        if (horizontalAlignment == HORIZONTAL_ALIGN_CENTER) {
            offsetX = (bitmapWidth - layoutWidth) / 2;
        }
        else if (horizontalAlignment == HORIZONTAL_ALIGN_RIGHT) {
            offsetX = bitmapWidth - layoutWidth;
        }

        int offsetY = 0;
        int verticalAlignment   = (alignment >> 4) & 0x0F;
        switch (verticalAlignment)
        {
            case VERTICAL_ALIGN_CENTER:
                offsetY = (bitmapHeight - layoutHeight) / 2;
                break;
            case VERTICAL_ALIGN_BOTTOM:
                offsetY = bitmapHeight - layoutHeight;
                break;
        }



        Bitmap bitmap = Bitmap.createBitmap(bitmapWidth, bitmapHeight, Bitmap.Config.ARGB_8888);
        Canvas canvas = new Canvas(bitmap);
        canvas.translate(offsetX, offsetY);
        if ( stroke )
        {
            paint.setARGB(strokeA, strokeR, strokeG, strokeB);
            layout.draw(canvas);
        }
        paint.setStyle(TextPaint.Style.FILL);
        paint.setARGB(fontTintA, fontTintR, fontTintG, fontTintB);
        layout.draw(canvas);

        Cocos2dxBitmap.initNativeObject(bitmap);
        return true;
    }


        private static TextPaint newPaint(final String fontName, final int fontSize) {
        final TextPaint paint = new TextPaint();
        paint.setTextSize(fontSize);
        paint.setAntiAlias(true);

        // Set type face for paint, now it support .ttf file.
        if (fontName.endsWith(".ttf")) {
            try {
                final Typeface typeFace = Cocos2dxTypefaces.get(
                        Cocos2dxBitmap.sContext, fontName);
                paint.setTypeface(typeFace);
            } catch (final Exception e) {
                Log.e("Cocos2dxBitmap", "error to create ttf type face: "
                        + fontName);

                // The file may not find, use system font.
                paint.setTypeface(Typeface.create(fontName, Typeface.NORMAL));
            }
        } else {
            paint.setTypeface(Typeface.create(fontName, Typeface.NORMAL));
        }

return paint;
}
    private static TextProperty computeTextProperty(final String string,
            final int width, final int height, final Paint paint) {
        final FontMetricsInt fm = paint.getFontMetricsInt();
        final int h = (int) Math.ceil(fm.bottom - fm.top);
        int maxContentWidth = 0;

        final String[] lines = Cocos2dxBitmap.splitString(string, width,
                height, paint);

        if (width != 0) {
            maxContentWidth = width;
        } else {
            // Compute the max width.
            int temp = 0;
            for (final String line : lines) {
                temp = (int) Math.ceil(paint.measureText(line, 0,
                        line.length()));
                if (temp > maxContentWidth) {
                    maxContentWidth = temp;
                }
            }
        }

        return new TextProperty(maxContentWidth, h, lines);
    }


    /*
     * If maxWidth or maxHeight is not 0, split the string to fix the maxWidth
     * and maxHeight.
     */
    private static String[] splitString(final String string,
            final int maxWidth, final int maxHeight, final Paint paint) {
        final String[] lines = string.split("\\n");
        String[] ret = null;
        final FontMetricsInt fm = paint.getFontMetricsInt();
        final int heightPerLine = (int) Math.ceil(fm.bottom - fm.top);
        final int maxLines = maxHeight / heightPerLine;

        if (maxWidth != 0) {
            final LinkedList<String> strList = new LinkedList<String>();
            for (final String line : lines) {
                /*
                 * The width of line is exceed maxWidth, should divide it into
                 * two or more lines.
                 */
                final int lineWidth = (int) Math.ceil(paint
                        .measureText(line));
                if (lineWidth > maxWidth) {
                    strList.addAll(Cocos2dxBitmap.divideStringWithMaxWidth(
                            line, maxWidth, paint));
                } else {
                    strList.add(line);
                }

                // Should not exceed the max height.
                if (maxLines > 0 && strList.size() >= maxLines) {
                    break;
                }
            }

            // Remove exceeding lines.
            if (maxLines > 0 && strList.size() > maxLines) {
                while (strList.size() > maxLines) {
                    strList.removeLast();
                }
            }

            ret = new String[strList.size()];
            strList.toArray(ret);
        } else if (maxHeight != 0 && lines.length > maxLines) {
            /* Remove exceeding lines. */
            final LinkedList<String> strList = new LinkedList<String>();
            for (int i = 0; i < maxLines; i++) {
                strList.add(lines[i]);
            }
            ret = new String[strList.size()];
            strList.toArray(ret);
        } else {
            ret = lines;
        }

        return ret;
    }

    private static LinkedList<String> divideStringWithMaxWidth(
        final String string, final int maxWidth, final Paint paint) {
        final int charLength = string.length();
        int start = 0;
        int tempWidth = 0;
        final LinkedList<String> strList = new LinkedList<String>();

        // Break a String into String[] by the width & should wrap the word.
        for (int i = 1; i <= charLength; ++i) {
            tempWidth = (int) Math.ceil(paint.measureText(string, start,
                    i));
            if (tempWidth >= maxWidth) {
                final int lastIndexOfSpace = string.substring(0, i)
                        .lastIndexOf(" ");

                if (lastIndexOfSpace != -1 && lastIndexOfSpace > start) {
                    // Should wrap the word.
                    strList.add(string.substring(start, lastIndexOfSpace));
                    i = lastIndexOfSpace + 1; // skip space
                } else {
                    // Should not exceed the width.
                    if (tempWidth > maxWidth) {
                        strList.add(string.substring(start, i - 1));
                        // Compute from previous char.
                        --i;
                    } else {
                        strList.add(string.substring(start, i));
                    }
                }

                // Remove spaces at the beginning of a new line.
                while (i < charLength && string.charAt(i) == ' ') {
                    ++i;
                }

                start = i;
            }
        }

        // Add the last chars.
        if (start < charLength) {
            strList.add(string.substring(start));
        }

        return strList;
    }

    private static String refactorString(final String string) {
        // Avoid error when content is "".
        if (string.compareTo("") == 0) {
            return " ";
        }

        /*
         * If the font of "\n" is "" or "\n", insert " " in front of it. For
         * example: "\nabc" -> " \nabc" "\nabc\n\n" -> " \nabc\n \n".
         */
        final StringBuilder strBuilder = new StringBuilder(string);
        int start = 0;
        int index = strBuilder.indexOf("\n");
        while (index != -1) {
            if (index == 0 || strBuilder.charAt(index - 1) == '\n') {
                strBuilder.insert(start, " ");
                start = index + 2;
            } else {
                start = index + 1;
            }

            if (start > strBuilder.length() || index == strBuilder.length()) {
                break;
            }

            index = strBuilder.indexOf("\n", start);
        }

        return strBuilder.toString();
    }

    private static void initNativeObject(final Bitmap bitmap) {
        final byte[] pixels = Cocos2dxBitmap.getPixels(bitmap);
        if (pixels == null) {
            return;
        }

        Cocos2dxBitmap.nativeInitBitmapDC(bitmap.getWidth(),
                bitmap.getHeight(), pixels);
    }

    private static byte[] getPixels(final Bitmap bitmap) {
        if (bitmap != null) {
            final byte[] pixels = new byte[bitmap.getWidth()
                    * bitmap.getHeight() * 4];
            final ByteBuffer buf = ByteBuffer.wrap(pixels);
            buf.order(ByteOrder.nativeOrder());
            bitmap.copyPixelsToBuffer(buf);
            return pixels;
        }

        return null;
    }

    private static int getFontSizeAccordingHeight(int height) {
        Paint paint = new Paint();
        Rect bounds = new Rect();

        paint.setTypeface(Typeface.DEFAULT);
        int incr_text_size = 1;
        boolean found_desired_size = false;

        while (!found_desired_size) {

            paint.setTextSize(incr_text_size);
            String text = "SghMNy";
            paint.getTextBounds(text, 0, text.length(), bounds);

            incr_text_size++;

            if (height - bounds.height() <= 2) {
                found_desired_size = true;
            }
            Log.d("font size", "incr size:" + incr_text_size);
        }
        return incr_text_size;
    }

    private static String getStringWithEllipsis(String string, float width,
            float fontSize) {
        if (TextUtils.isEmpty(string)) {
            return "";
        }

        TextPaint paint = new TextPaint();
        paint.setTypeface(Typeface.DEFAULT);
        paint.setTextSize(fontSize);

        return TextUtils.ellipsize(string, paint, width,
                TextUtils.TruncateAt.END).toString();
    }

    // ===========================================================
    // Inner and Anonymous Classes
    // ===========================================================

    private static class TextProperty {
        /** The max width of lines. */
        private final int mMaxWidth;
        /** The height of all lines. */
        private final int mTotalHeight;
        private final int mHeightPerLine;
        private final String[] mLines;

        TextProperty(final int maxWidth, final int heightPerLine,
                final String[] lines) {
            this.mMaxWidth = maxWidth;
            this.mHeightPerLine = heightPerLine;
            this.mTotalHeight = heightPerLine * lines.length;
            this.mLines = lines;
        }
    }
}
