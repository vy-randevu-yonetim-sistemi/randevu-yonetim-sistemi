# Klinik Randevu Yönetim Sistemi

**Hazırlayanlar:**  
Yusuf İslam Çelik, Muhammed Celil Ayhan, Recep Kaan Karaman, Ömer Faruk Arı, Yavuz Alp Özgür  
**Tarih:** 11.05.2025

> Github link: [Klinik Randevu Yönetim Sistemi](https://github.com/vy-randevu-yonetim-sistemi/randevu-yonetim-sistemi)

---

## 1. Giriş

Bu rapor, **Klinik Randevu Yönetim Sistemi** projesi kapsamında geliştirilen arayüz (frontend) bileşenlerinin tasarımını, kullanılan teknolojileri ve uygulanan özellikleri belgelemek amacıyla hazırlanmıştır.  
Projenin amacı, bir klinikte hastaların randevularının kolay ve etkili bir şekilde yönetilmesini sağlamaktır.

---

## 2. Kullanılan Teknolojiler

- **Qt Framework** (Qt Creator IDE)
- **C++** (GUI destekli uygulama geliştirme)
- **QWidgets** (QPushButton, QComboBox, QLabel, QLineEdit, vb.)

---

## 3. Arayüz Tasarımı

Proje arayüzü, kullanıcı dostu olacak şekilde tasarlanmıştır. Aşağıdaki temel bileşenler kullanılmıştır:

- **QMainWindow**: Ana pencere, tüm bileşenleri kapsar.
- **QComboBox**: Kullanıcının gerçekleştirmek istediği işlemi seçmesi için kullanılır (randevu ekleme, silme, güncelleme vb.).
- **QPushButton**: Seçilen işlemi tetiklemek amacıyla her işleme özel butonlar tanımlanmıştır.
- **QLineEdit / QDateEdit**: Kullanıcıdan bilgi almak için giriş alanları kullanılmıştır.

---

## 4. Uygulanan Özellikler

Projenin şu ana kadar arayüz üzerinden desteklediği işlevler aşağıdaki gibidir:

### 1. Randevu Ekleme

- Hasta adı, doktor adı, tarih ve saat bilgileri girilerek randevu oluşturulabilir.
- Girdi doğrulaması yapılmıştır (boş alanlar kontrol edilir).

### 2. Randevu Silme

- Randevuyu alan kişi, istediği takdirde randevusunu iptal edebilir.

### 3. Randevuları Listeleme

- Sistemdeki tüm randevular **QTableWidget** veya **QTextEdit** ile görüntülenebilir.
- Görüntülenen randevular, doktorlar için randevu takibi amacıyla kullanılabilir.

---

## 5. Kullanıcı Deneyimi (UX) Odaklı Yaklaşımlar

- Renkli butonlar ve ikonlarla görsel geri bildirim sağlanmıştır.
- Uyarı pencereleri (**QMessageBox**) ile kullanıcı yönlendirmeleri yapılmıştır.
- Arayüz, farklı ekran çözünürlüklerine uygun olarak dinamik boyutlandırılmıştır.

---

## 6. Sonuç ve Değerlendirme

**Klinik Randevu Yönetim Sistemi** projesi başarıyla tamamlanmıştır.  
Proje kapsamında kullanıcı dostu bir arayüz geliştirilmiş ve arka planda etkili çalışan veri yapıları ile desteklenmiştir.  
Tüm temel işlemler (randevu ekleme, silme, güncelleme, listeleme) eksiksiz şekilde uygulanmış ve arayüz ile tam entegre edilmiştir.

Projenin sonunda, sistem hem teknik olarak sağlam hem de kullanıcı açısından anlaşılır ve pratik bir uygulama haline gelmiştir.  
Arayüz öğeleri (**QComboBox**, **QPushButton**, **QTextEdit** vb.) düzenli bir yapı içinde tasarlanarak hem görsellik hem de işlevsellik ön planda tutulmuştur.

Bu proje sayesinde hem **C++ GUI programlama** hem de **veri yapıları** (bağlı liste, kuyruk, stack, hashmap) konularında uygulamalı deneyim kazanılmıştır.

---

## Veri Yapıları ve Zaman Karmaşıklıkları Analizi

### 1. Çift Yönlü Bağlı Liste (`DoubleLinkedList`)

**Kullanım Amaçları:**
- Randevuların bellek üzerinde dinamik ve sıralı şekilde tutulması
- Randevuların hızlı bir şekilde başa/sona eklenebilmesi veya silinebilmesi
- Veritabanı dışında geçici işlem yaparken liste halinde yönetim

---

#### 📊 Zaman Karmaşıklıkları (Big-O Notation)

| İşlem Türü        | Ortalama Durum | En Kötü Durum | Açıklama                                                       |
|-------------------|----------------|---------------|----------------------------------------------------------------|
| `addFront()`      | O(1)           | O(1)          | Yeni düğüm head'e bağlanır, pointerlar güncellenir             |
| `addBack()`       | O(1)           | O(1)          | Yeni düğüm tail'e bağlanır, tail güncellenir                   |
| `insertSorted()`  | O(n)           | O(n)          | Tarih/saat sırasına göre doğru yere yerleştirme gerekir        |
| `removeFront()`   | O(1)           | O(1)          | Head düğümü silinir, yeni head güncellenir                     |
| `removeBack()`    | O(1)           | O(1)          | Tail düğümü silinir, yeni tail güncellenir                     |
| `remove(T value)` | O(n)           | O(n)          | Belirtilen veriyi arar ve ilk eşleşen düğümü siler             |
| `search(value)`   | O(n)           | O(n)          | Lineer arama gerekir, indeksleme yok                           |
| `traverse()`      | O(n)           | O(n)          | Tüm liste boyunca işlem yapılır (örneğin filtreleme, yazdırma) |

---

#### ✅ Avantajlar

- **Çift Yönlü Erişim:** `prev` ve `next` ile hem ileri hem geri gezinilebilir.
- **Dinamik Boyut:** Bellekte yerleşim dinamik olduğu için liste büyüyebilir/küçülebilir.
- **Sıralı Ekleme:** Liste sıralı tutulabilir (örneğin tarih + saat’e göre).
- **Hızlı Uç Erişimi:** Baş ve son düğümlere erişim ve işlem sabit sürede yapılır.

---

#### ⚠️ Dezavantajlar

- **Rastgele Erişim Yok:** İndeks ile erişim mümkün değildir (`O(1)` erişim için dizi tercih edilmeli).
- **Bellek Maliyeti Yüksek:** Her düğümde `prev`, `next` ve veri alanları tutulur → daha fazla bellek kullanımı.
- **Sıralı Ekleme Maliyeti:** Yeni elemanlar eklenmeden önce tüm liste taranmak zorunda kalabilir.

---

#### 🎯 Uygun Kullanım Senaryoları

- Randevuların tarih-saat sırasına göre tutulduğu dinamik listeler
- Baş ve sondan hızlı veri eklenip çıkarılması gereken yapılar (örneğin bekleme listeleri)

---

### 2. Kuyruk (`Queue<T>`)

**Kullanım Amaçları:**
- Doktorlara gelen hastaları geliş sırasına göre sıraya almak (FIFO: First-In First-Out)
- Randevuların çağrılma sırasını yönetmek
- Zaman uyumlu işleme yapılacak verileri sırayla ele almak

---

#### 📊 Zaman Karmaşıklıkları (Big-O Notation)

| İşlem       | Ortalama Durum | En Kötü Durum | Açıklama                                        |
|-------------|----------------|---------------|-------------------------------------------------|
| `enqueue()` | O(1)           | O(1)          | Arka düğüme ekleme, sadece pointer güncellenir  |
| `dequeue()` | O(1)           | O(1)          | Ön düğümden çıkarma, sadece pointer güncellenir |
| `front()`   | O(1)           | O(1)          | İlk sıradaki elemana doğrudan erişim            |
| `isEmpty()` | O(1)           | O(1)          | Null kontrolüyle sabit sürede durum bilgisi     |
| `size()`    | O(1)           | O(1)          | Sayaç tutuluyorsa sabit sürede boyut öğrenilir  |
| `clear()`   | O(n)           | O(n)          | Tüm elemanlar sırayla silinir                   |

---

#### ✅ Avantajlar

- **FIFO Doğası:** İlk gelen ilk çıkar; özellikle adil randevu yönetiminde önemlidir.
- **Sabit Süreli İşlem:** Ekleme/çıkarma işlemleri sabit sürede yapılır → yüksek performans.
- **Uygulama Kolaylığı:** Dinamik liste tabanlı yapı ile karmaşık bellek yönetimine gerek yok.
- **Kapsülleme:** Hastaların randevu sırasında karışmasını önler.

---

#### ⚠️ Dezavantajlar

- **Ortadaki Elemana Erişim Zordur:** Ancak sırayı tamamen boşaltarak ulaşılabilir → `O(n)` zaman.
- **Sadece Baş ve Son Kullanılır:** Rastgele erişim yapılamaz, sadece `front()` ve `rear` uçları erişilebilir.
- **Bellek Temizliği Gerekebilir:** Uygun `clear()` çağrılmazsa bellek sızıntısı olabilir.

---

#### 🎯 Uygun Kullanım Senaryoları

- Doktorlara gelen hastaların çağrı sırasının belirlenmesi
- Arka planda işlem sırasına alınacak görevlerin yönetimi
- Yazıcı kuyruğu, işlem sırası, destek hattı yönetimi gibi senaryolar

---

### 3. Stack (`Stack<T>`)

**Kullanım Amaçları:**
- İşlenen hastaların geçmişini kaydetmek (LIFO: Last-In First-Out)
- "Geri Al" özelliği gibi işlemlerde son işleme geri dönebilmek
- Geçici olarak işlenmiş randevuların yığın olarak tutulması

---

#### 📊 Zaman Karmaşıklıkları (Big-O Notation)

| İşlem       | Ortalama Durum | En Kötü Durum | Açıklama                                                                  |
|-------------|----------------|---------------|---------------------------------------------------------------------------|
| `push()`    | O(1)           | O(1)          | Yeni eleman en üste eklenir, sadece pointer güncellenir                   |
| `pop()`     | O(1)           | O(1)          | En üstteki eleman çıkarılır, pointer güncellenir                          |
| `top()`     | O(1)           | O(1)          | En üstteki elemana erişim sağlanır                                        |
| `isEmpty()` | O(1)           | O(1)          | Stack’in boş olup olmadığını kontrol eder                                 |
| `size()`    | O(n)           | O(n)          | Tüm elemanları sayarak hesaplanır (isteğe bağlı sayaçla O(1) yapılabilir) |
| `clear()`   | O(n)           | O(n)          | Tüm elemanlar sırayla boşaltılır                                          |

---

#### ✅ Avantajlar

- **Son Eklenen İlk Çıkar:** İşlenen son hastaya ulaşmak çok hızlıdır.
- **Basit ve Etkili:** Tek uçtan işlem yapılır, bu da uygulama açısından sadelik sağlar.
- **Geri Alma (Undo):** Geri alma, iptal etme veya işlem geçmişini tutmak için idealdir.
- **Bellek Yönetimi:** Dinamik yapı ile esnek boyutlandırma mümkündür.

---

#### ⚠️ Dezavantajlar

- **Sadece En Üst Erişilebilir:** Ortadaki veya alttaki verilere erişim için tüm stack’i boşaltmak gerekir.
- **Taramalar Maliyetlidir:** Tüm veriye ihtiyaç varsa `O(n)` zaman gerekir.
- **Sıralama Yoktur:** Elemanlar sıralı değildir; sadece işlem sırasına göre saklanır.

---

#### 🎯 Uygun Kullanım Senaryoları

- İşlenen randevuların geçmişini göstermek
- Geri al (undo) işlemleri (örneğin yanlış hastayı ileri alma)
- Fonksiyon çağrıları, işlem geçmişi, geçici geri izleme gereken durumlar

---

### 4. Hash Table

**Kullanım Amaçları:**
- Hastaların randevularını hızlı bir şekilde TC numarasına göre sorgulamak.
- Randevuları yönetirken veritabanındaki verilere hızlı erişim sağlamak.
- Randevu arama işlemlerinin optimize edilmesi ve veritabanı ile senkronize şekilde çalışmak.

---

#### 📊 Zaman Karmaşıklıkları (Big-O Notation)

| İşlem         | Ortalama Durum | En Kötü Durum | Açıklama                                                                  |
|---------------|----------------|---------------|---------------------------------------------------------------------------|
| `insert()`    | O(1)           | O(n)          | Yeni eleman ekler, ancak çakışma durumunda (collision) çözümleme gerekir   |
| `delete()`    | O(1)           | O(n)          | Eleman silinir, çakışma çözümü gerektirebilir                              |
| `search()`    | O(1)           | O(n)          | İlgili öğe bulunur, ancak kötü durum çakışma ile ortaya çıkabilir         |
| `resize()`    | O(n)           | O(n)          | Hash table kapasitesi arttırıldığında tüm öğeler yeniden yerleştirilir    |
| `clear()`     | O(n)           | O(n)          | Tüm elemanlar silinir                                                       |

---

#### ✅ Avantajlar

- **Hızlı Erişim:** Ortalama durumda elemanlara erişim sabit zaman diliminde yapılır (`O(1)`).
- **Yüksek Performans:** Veritabanı ile uyumlu çalışarak randevulara hızlı erişim sağlar.
- **Kolay Yönetim:** Çakışma çözümleme stratejileriyle (open addressing, chaining) hızlı ve etkili veri yönetimi yapılır.

---

#### ⚠️ Dezavantajlar

- **Çakışma:** Aynı hash değerine sahip öğeler olursa, ekleme işlemi karmaşıklaşabilir.
- **Bellek Kullanımı:** Hash table’ın büyüklüğü arttıkça daha fazla bellek kullanımı gerekir.
- **Sıralama Yoktur:** Hash table, elemanları sırasız şekilde saklar; sıralama işlemi zorlaşır.

---

#### 🎯 Uygun Kullanım Senaryoları

- Hastaların TC numarasına göre randevuların hızlıca aranması ve yönetilmesi
- Veritabanından alınan randevu verilerinin hızlı sorgulanması ve düzenlenmesi
- Yüksek performans gerektiren arama işlemleri

## Genel Performans Özeti

| Veri Yapısı      | Kullanım Durumu                        | Ortalama Performans | Açıklama                                           |
|------------------|----------------------------------------|---------------------|----------------------------------------------------|
| DoubleLinkedList | Sıralı liste tutma, gezme, silme       | O(n)                | Sıralı yerleştirme ve silme için tüm liste gezilir |
| Queue            | Bekleme sırası yönetimi (doktor bazlı) | O(1)                | FIFO yapısı, uçtan ekleme/çıkarma sabit sürede     |
| Stack            | İşlenen hasta geçmişini takip etme     | O(1)                | LIFO yapısı, üst elemanla sabit süreli işlem       |
| HashTable        | TC ile randevu arama/sorgulama         | O(1) (ortalama)     | Anahtar bazlı hızlı erişim, zincirleme kullanılır  |

---

### Notlar:

- `DoubleLinkedList`: Randevular tarih-saat sırasına göre tutulur; araya ekleme veya silme gerektiğinde performans düşer.
- `Queue`: Her doktorun bekleme sırası bu yapıyla modellenir; sıradaki hasta kolayca çağrılır.
- `Stack`: Son işlenen hastaları tutmak ve geriye dönük listeleme için kullanılır.
- `HashTable`: Belirli bir TC'ye ait tüm randevulara anında erişim sağlar; zincirleme yöntemi kullanıldığı için çakışmalar etkili yönetilir.
