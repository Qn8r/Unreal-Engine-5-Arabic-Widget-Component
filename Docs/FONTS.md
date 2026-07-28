# الخطوط العربية المرفقة

تتضمن الإضافة ثماني عائلات خطوط تدعم العربية. كل عائلة متاحة كأصلي `Font`
و`Font Face` جاهزين للاستخدام تحت المسار `/ArabicWidget/Fonts`.

| العائلة | الاستخدام المقترح | أصل Font في Unreal |
| --- | --- | --- |
| Amiri | النصوص الكلاسيكية والمتون الطويلة بخط النسخ | `F_Amiri` |
| Cairo | الواجهات الحديثة والعناوين | `F_Cairo` |
| Tajawal | عناوين وعناصر الواجهة الواضحة | `F_Tajawal` |
| Noto Sans Arabic | الواجهات العامة وتغطية محارف واسعة | `F_NotoSansArabic` |
| Noto Naskh Arabic | المتون المقروءة بأسلوب النسخ | `F_NotoNaskhArabic` |
| Noto Kufi Arabic | التصميم الهندسي بأسلوب كوفي | `F_NotoKufiArabic` |
| Reem Kufi | العناوين الزخرفية بأسلوب كوفي | `F_ReemKufi` |
| Readex Pro | النصوص الثنائية العربية واللاتينية | `F_ReadexPro` |

خط Amiri هو الخط الافتراضي للمكوّن. لتغييره، افتح خاصية
**Appearance > Font** واختر أي أصل يبدأ بـ`F_` من مجلد `Fonts` الخاص بالإضافة.

تحتفظ الخطوط المتغيرة بالمحاور التي تدعمها داخل ملف مصدر واحد. يستورد Unreal
كل ملف كـFont مركّب وقت التشغيل مع Font Face مضمن.

توزع العائلات الثماني وفق **SIL Open Font License 1.1**. توجد ملفات الخط
الأصلية ونص الترخيص وبيانات Google Fonts وإصدار المصدر المثبّت وبصمات
`SHA-256` داخل `Resources/Fonts`. راجع `THIRD_PARTY_NOTICES.md` و
`Resources/Fonts/MANIFEST.json`.
