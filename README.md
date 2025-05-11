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

- Kullanıcıdan hasta adı ya da tarih gibi kriterlere göre randevu silinebilir.

### 3. Randevuları Listeleme

- Sistemdeki tüm randevular **QTableWidget** veya **QTextEdit** ile görüntülenebilir.

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

**Kullanım:**
- Randevuları bellekte sıralı tutmak
- Randevu listeleme, silme, sıralı ekleme

**Zaman Karmaşıklıkları:**

| İşlem               | Karmaşıklık |
|---------------------|-------------|
| Ekleme (baş/son)    | O(1)        |
| Sıralı ekleme       | O(n)        |
| Silme (eşleşme ile) | O(n)        |
| Arama (traverse)    | O(n)        |

**Avantajlar:**
- Çift yönlü gezinme (prev/next)
- Sıralı ekleme yapılabilir

**Dezavantajlar:**
- Rastgele erişim yoktur
- Her düğüm için ek bellek gerekir

---

### 2. Kuyruk (`Queue<T>`)

**Kullanım:**
- Doktora gelen hastaları sıraya almak (FIFO)

**Zaman Karmaşıklıkları:**

| İşlem     | Karmaşıklık |
|-----------|-------------|
| enqueue() | O(1)        |
| dequeue() | O(1)        |
| front()   | O(1)        |
| isEmpty() | O(1)        |

**Avantajlar:**
- Bekleme sırası düzenlemede çok verimli
- Sabit zamanda ekleme/çıkarma yapılır

**Dezavantajlar:**
- Ortadaki elemana erişmek zordur (O(n))

---

### 3. Stack (`Stack<T>`)

**Kullanım:**
- İşlenen hastaları (geçmiş) takip etmek (LIFO)

**Zaman Karmaşıklıkları:**

| İşlem     | Karmaşıklık |
|-----------|-------------|
| push()    | O(1)        |
| pop()     | O(1)        |
| top()     | O(1)        |
| isEmpty() | O(1)        |

**Avantajlar:**
- Son işlenen hasta bilgisine hızlı erişim
- Geri alma işlemleri için uygundur

**Dezavantajlar:**
- Sadece en üst eleman erişilebilir
- Tam tarama gerekiyorsa O(n)

---

### 4. Hash Tablosu (`HashTable`)

**Kullanım:**
- TC numarasına göre hızlı randevu arama

**Zaman Karmaşıklıkları (ortalama durumda):**

| İşlem    | Karmaşıklık |
|----------|-------------|
| add()    | O(1)        |
| search() | O(1)        |

**Avantajlar:**
- Hızlı erişim sağlar
- TC gibi benzersiz verilerle doğrudan çalışır

**Dezavantajlar:**
- Çakışma durumlarında performans düşebilir
- Sabit boyutlu tablolarda gereksiz bellek kullanılabilir

---

## Genel Performans Özeti

| Veri Yapısı      | Kullanım Durumu                  | Ortalama Performans |
|------------------|----------------------------------|---------------------|
| DoubleLinkedList | Sıralı liste tutma, gezme, silme | O(n)                |
| Queue            | Bekleme sırası (doktor bazlı)    | O(1)                |
| Stack            | İşlenen hasta listesini takip    | O(1)                |
| HashTable        | TC ile randevu sorgulama         | O(1)                |