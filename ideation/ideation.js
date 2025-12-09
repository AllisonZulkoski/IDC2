document.addEventListener('DOMContentLoaded', () => {
    const lastImage = document.querySelector('.full-screen-image:last-of-type');

    const observer = new IntersectionObserver((entries) => {
        entries.forEach(entry => {
            if (entry.isIntersecting) {
                lastImage.classList.add('visible');
            }
        });
    });

    observer.observe(lastImage);
});
